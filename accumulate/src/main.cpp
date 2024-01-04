#include <iostream>
#include <thread>
#include <string>
#include <future>
#include <vector>
#include <list>
#include <mutex>
#include <memory>
#include <numeric>

template <typename T>
void print(T &&t)
{
    std::cout << std::forward<T>(t) << std::endl;
}

template <typename It, typename T>
constexpr T myAccumulate(It begin, It end, T first)
{
    for (; begin != end; ++begin)
    {
        first = std::move(first) + *begin;
    }
    return first;
}

template <typename First, typename... Args>
auto sum(First first, Args... args) -> decltype(first)
{
    const auto values = {first, args...};
    // return std::accumulate(values.begin(), values.end(), First{0});
    return myAccumulate(values.begin(), values.end(), First{0});
}

int main()
{
    print(sum(1, 2, 3, 4, 5));
}
