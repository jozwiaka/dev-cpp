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

class Target
{
public:
    virtual void request() = 0;
    virtual ~Target() {}
};

class Adaptee
{
public:
    void specificRequest()
    {
        print(
            "Adaptee's specific request");
    }
};

class Adapter : public Target
{
private:
    std::unique_ptr<Adaptee> m_adaptee;

public:
    Adapter() : m_adaptee(std::make_unique<Adaptee>()) {}

    void request() override
    {
        m_adaptee->specificRequest();
    }
};

int main()
{
    std::unique_ptr<Target> target = std::make_unique<Adapter>();
    target->request();
}
