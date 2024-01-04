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

template <typename T>
auto &buffer(T &t)
{
    return t;
}

struct Entity
{
    int value;

    Entity() {}
    Entity(int value) : value{value} {}

    auto getValueCopy()
    {
        return [*this]
        { return value; };
    }
    auto getValueRef()
    {
        return [this]
        { return value; };
    }
};

int main()
{
    // mutable keyword is needed to modify x
    auto generator = [x = 0]() mutable
    {
        return x++;
    };

    print(generator()); // 0
    print(generator()); // 1
    print(generator()); // 2

    auto p = std::make_unique<int>(1);
    // auto task1 = [=] {*p =  5;}; //error - unique_ptr cannot be coppied
    auto task2 = [ptr = std::move(p)]
    {
        *ptr = 5;
    };

    int x = 2;
    auto f = [&val = x]
    {
        ++val;
    };
    f();
    print(x); // 3

    auto g = [](auto &x) -> auto &
    {
        return buffer(x);
    };
    int y = 5;
    int &z = g(y);
    z++;
    print(y);

    Entity e{5};
    auto valueCopy = e.getValueCopy();
    auto valueRef = e.getValueRef();
    e.value++;
    print(valueCopy()); // 5
    print(valueRef());  // 6

    // Template syntax for lambdas

    auto fT = []<typename T>(std::vector<T> v)
    {for(const auto& vi : v) {print(vi);} };
    std::vector<std::string> v{"Hello", "World"};
    fT(v);
}
