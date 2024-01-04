// OPen new WSL terminal and run telnet 127.0.0.1 8888
// Connected to 127.0.0.1.
// Escape character is '^]'. //Ctrl + ]
// Type a message and press Enter:

// Hello, server!
// Hello, server!

#include <iostream>
#include <boost/asio.hpp>

using boost::asio::ip::tcp;

class Session : public std::enable_shared_from_this<Session>
{
public:
    Session(tcp::socket socket) : socket_(std::move(socket)) {}

    void start()
    {
        doRead();
    }

private:
    void doRead()
    {
        auto self(shared_from_this());
        socket_.async_read_some(boost::asio::buffer(data_),
                                [this, self](boost::system::error_code ec, std::size_t length)
                                {
                                    if (!ec)
                                    {
                                        doWrite(length);
                                    }
                                });
    }

    void doWrite(std::size_t length)
    {
        auto self(shared_from_this());
        boost::asio::async_write(socket_, boost::asio::buffer(data_, length),
                                 [this, self](boost::system::error_code ec, std::size_t /* length */)
                                 {
                                     if (!ec)
                                     {
                                         doRead();
                                     }
                                 });
    }

    tcp::socket socket_;
    std::array<char, 1024> data_;
};

class Server
{
public:
    Server(boost::asio::io_context &ioContext, short port)
        : acceptor_(ioContext, tcp::endpoint(tcp::v4(), port)),
          socket_(ioContext)
    {
        doAccept();
    }

private:
    void doAccept()
    {
        acceptor_.async_accept(socket_,
                               [this](boost::system::error_code ec)
                               {
                                   if (!ec)
                                   {
                                       std::make_shared<Session>(std::move(socket_))->start();
                                   }

                                   doAccept();
                               });
    }

    tcp::acceptor acceptor_;
    tcp::socket socket_;
};

int main()
{
    try
    {
        boost::asio::io_context ioContext;
        Server server(ioContext, 8888);
        ioContext.run();
    }
    catch (const std::exception &e)
    {
        std::cerr << "Exception: " << e.what() << std::endl;
    }

    return 0;
}
