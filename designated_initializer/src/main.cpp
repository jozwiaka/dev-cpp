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
    int x;
    int y = 2;
    int z;
};

int main()
{
    A a{.x = 1, .z = 3};
}
