#include <iostream>
#include <thread>
#include <string>
#include <future>
#include <vector>
#include <list>
#include <mutex>

template <typename T>
void print(T &&t)
{
    std::cout << t << std::endl;
}

class Singleton
{
public:
    static Singleton &getInstance()
    {
        static Singleton instance;
        return instance;
    }

    Singleton(const Singleton &) = delete;
    void operator=(const Singleton &) = delete;

private:
    Singleton() = default;
};

int main()
{
    // it has to be reference, because copy constructor is deleted
    Singleton &singleton = Singleton::getInstance();
}
