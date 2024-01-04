#include <iostream>
#include <thread>
#include <string>
#include <future>
#include <vector>
#include <list>
#include <mutex>
#include <ranges>
#include <algorithm>

template <typename T>
void print(T &&t)
{
    std::cout << t << std::endl;
}

int main()
{
    std::vector<int> numbers = {1, 2, 3, 4, 5};

    // pipe "|" syntax of composing the views
    auto result = numbers | std::views::filter([](int n)
                                               { return n % 2 == 0; }) |
                  std::views::transform([](int n)
                                        { return n * n; });

    for (int n : result)
    {
        print(n);
    }
}
