// server.cpp
#include <iostream>
#include <boost/asio.hpp>
#include <array>

// socket() -> bind() -> listen() -> accept() -> [read, write]

class TCPServer
{
public:
    TCPServer(boost::asio::io_service &ioService, short port)
        : m_Acceptor{ioService, boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), port)},
          m_Socket{ioService}
    {
        StartAccept();
    }

private:
    void StartAccept()
    {
        m_Acceptor.async_accept(m_Socket,
                                [this](const boost::system::error_code &ec)
                                {
                                    if (!ec)
                                    {
                                        std::cout << "Accepted connection from: " << m_Socket.remote_endpoint() << std::endl;

                                        StartRead();
                                    }
                                    StartAccept();
                                });
    }

    void StartRead()
    {
        boost::asio::async_read(
            m_Socket,
            boost::asio::buffer(m_Data),
            [this](const boost::system::error_code &ec, std::size_t length)
            {
                if (!ec)
                {
                    StartWrite(length);
                }
            });
    }

    void StartWrite(std::size_t length)
    {
        boost::asio::async_write(
            m_Socket,
            boost::asio::buffer(m_Data, length),
            [this](const boost::system::error_code &ec, std::size_t /*length*/)
            {
                if (!ec)
                {
                    StartRead();
                }
            });
    }

private:
    boost::asio::ip::tcp::acceptor m_Acceptor;
    boost::asio::ip::tcp::socket m_Socket;
    std::array<char, 1024> m_Data;
};

int main()
{
    try
    {
        std::cout << "Running server...\n";
        boost::asio::io_service ioService;
        TCPServer server(ioService, 8080);
        ioService.run();
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }

    return 0;
}
