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

int main()
{
    // std::clamp(a, min, max)
    print(std::clamp(100, -1, 1));  // 1
    print(std::clamp(-100, -1, 1)); //-1
}
