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

class Component
{
public:
    virtual void operation() = 0;
    virtual ~Component() {}
};

class ComponentA : public Component
{
public:
    void operation() override
    {
        print("ComponentA operation");
    }
};

class Decorator : public Component
{
public:
    Decorator(std::unique_ptr<Component> c) : component(std::move(c)) {}

    void operation() override
    {
        if (component)
        {
            component->operation();
        }
    }

protected:
    std::unique_ptr<Component> component;
};

class Decorator1 : public Decorator
{
public:
    Decorator1(std::unique_ptr<Component> c) : Decorator(std::move(c))
    {
    }

    void operation() override
    {
        Decorator::operation();
        print("Decorator1 operation");
    }
};

int main()
{
    std::unique_ptr<Component> component = std::make_unique<ComponentA>();
    std::unique_ptr<Decorator> decorated = std::make_unique<Decorator1>(std::move(component));
    decorated->operation();
}
