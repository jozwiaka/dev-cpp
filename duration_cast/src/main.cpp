#include <iostream>
#include <thread>
#include <string>
#include <future>
#include <vector>
#include <list>
#include <mutex>
#include <memory>
#include <chrono>

template <typename T>
void print(T &&t)
{
    std::cout << std::forward<T>(t) << std::endl;
}

int main()
{
    using namespace std::chrono_literals;
    auto day = 24h;
    print(day.count());
    print(std::chrono::duration_cast<std::chrono::minutes>(day).count());
}
