#include <iostream>
#include <thread>
#include <string>
#include <future>
#include <vector>
#include <list>
#include <mutex>
#include <memory>

template <typename T>
void print(T &&t)
{
    std::cout << std::forward<T>(t) << std::endl;
}

// Observer (Client)
class Client
{
public:
    virtual void Update(const std::string &message) = 0;
};

// Concrete Observer (Concrete Client)
class ChatClient : public Client
{
public:
    ChatClient(const std::string &name) : m_Name{name} {}

    void Update(const std::string &message) override
    {
        std::cout << "[" << m_Name << "] " << message << std::endl;
    }

private:
    std::string m_Name;
};

// Subject (Server)
class Server
{
public:
    void RegisterClient(Client *client)
    {
        m_Clients.push_back(client);
    }

    void SendMessage(const std::string &message)
    {
        for (auto client : m_Clients)
        {
            client->Update(message);
        }
    }

private:
    std::vector<Client *> m_Clients;
};

int main()
{
    Server server;

    ChatClient chatClient1{"User1"};
    ChatClient chatClient2{"User2"};

    server.RegisterClient(&chatClient1);
    server.RegisterClient(&chatClient2);

    // Message from server to all users
    server.SendMessage("Welcome in ChatApp!");
}
