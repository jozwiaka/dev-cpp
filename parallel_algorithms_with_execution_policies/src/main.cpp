#include <iostream>
#include <vector>
#include <algorithm>
#include <execution>
#include <array>

template <typename T>
void print(T &&t)
{
    std::cout << t << std::endl;
}

int main()
{
#define ALGHORITHM_PAR 1
#if ALGHORITHM_PAR
    std::vector<int> ns = {1, 2, 3, 4, 5};
    std::vector<int> squares(ns.size());
    squares.push_back(6); // 6 wont be squared later on

    // C++17 parallel algorithms with execution policies, enabling easier parallelization of code
    std::sort(std::execution::par, ns.begin(), ns.end());
    std::transform(std::execution::par, ns.begin(), ns.end(), squares.begin(), [](int n)
                   { return n * n; });
    for (const auto &ni : squares)
    {
        print(ni);
    }
    print("-------------------------------------------------------");
#endif

//  When using parallel execution policy, it is the programmer's responsibility to avoid data races and dead locks
#define DATA_RACE 1
#if DATA_RACE
    constexpr int SIZE = 1000;
    std::array<int, SIZE> a;
    for (int i = 0; i < SIZE; ++i)
    {
        a[i] = i;
    }
    std::vector<int> v;
    std::for_each(std::execution::par, std::begin(a), std::end(a), [&](int i)
                  {
                      v.push_back(i); // Error: data race
                  });

    for (int i = 0; i < SIZE; ++i)
    {
        print(v[i]);
    }
#endif
}
