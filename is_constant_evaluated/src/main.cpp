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

constexpr bool isCompileTime()
{
    return std::is_constant_evaluated();
}

int main()
{
    constexpr bool a = isCompileTime();
    bool b = isCompileTime();

    print(a);
    print(b);
}
