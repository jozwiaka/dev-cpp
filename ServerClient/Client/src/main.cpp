// client.cpp
#include <iostream>
#include <boost/asio.hpp>
#include <array>

class TCPClient
{
public:
    TCPClient(boost::asio::io_service &ioService, const std::string &host, const std::string &port)
        : m_Resolver(ioService),
          m_Socket(ioService)
    {
        Resolve(host, port);
    }

private:
    void Resolve(const std::string &host, const std::string &port)
    {
        boost::asio::ip::tcp::resolver::query query(host, port);
        m_Resolver.async_resolve(
            query,
            [this](const boost::system::error_code &ec, boost::asio::ip::tcp::resolver::iterator it)
            {
                if (!ec)
                {
                    StartConnect(it);
                }
            });
    }

    void StartConnect(boost::asio::ip::tcp::resolver::iterator it)
    {
        boost::asio::async_connect(
            m_Socket,
            it,
            [this](const boost::system::error_code &ec, const boost::asio::ip::tcp::resolver::iterator &)
            {
                if (!ec)
                {
                    std::cout << "Connected to server.\n";
                    StartWrite();
                }
            });
    }

    void StartWrite()
    {
        std::cout << "Enter message: ";
        std::cin.getline(m_Data.data(), m_Data.size());
        boost::asio::async_write(
            m_Socket,
            boost::asio::buffer(m_Data),
            [this](const boost::system::error_code &ec, std::size_t /*length*/)
            {
                if (!ec)
                {
                    StartRead();
                }
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
                    std::cout << "Received from server: " << std::string(m_Data.data(), length) << "\n";
                    StartWrite();
                }
            });
    }

private:
    boost::asio::ip::tcp::resolver m_Resolver;
    boost::asio::ip::tcp::socket m_Socket;
    std::array<char, 1024> m_Data;
};

int main()
{
    try
    {
        boost::asio::io_service ioService;
        TCPClient client(ioService, "127.0.0.1", "8080");
        ioService.run();
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }

    return 0;
}
