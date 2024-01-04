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

struct A
{
    virtual void f();
};

struct B : A
{
    virtual void f() final;
};

struct C : B
{
    // virtual void f(); // error
};

struct D final
{
};

// struct E : D // error
// {
// };

int main()
{
}
