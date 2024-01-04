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

template <typename T, typename U>
auto add11(T a, U b) -> decltype(a + b) // C++11
{
    return a + b;
}
template <typename T, typename U>
auto add14(T a, U b) -> decltype(auto) // C++14
{
    return a + b;
}
template <typename T, typename U>
auto add20(T a, U b) // C++20 ?
{
    return a + b;
}

int main()
{
    print(add11(1, 2));
    print(add14(1, 2));
    print(add20(1, 2));
}
