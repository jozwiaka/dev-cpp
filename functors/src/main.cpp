#include <iostream>
#include <thread>
#include <string>
#include <future>
#include <vector>
#include <list>
#include <mutex>
#include <memory>
#include <functional>
#define LINE std::cout << "------------------------------------------\n";

template <typename T>
void print(T &&t)
{
    std::cout << std::forward<T>(t) << std::endl;
}

// Functor = class which overloads the function call operator operator().
// NOTE: The number of arguments the operator() function takes doesn't affect wheter it qaulifies as a functor; what matters is that it overloads the function call operator
// NOTE: Lambda is a functor
class Functor
{
public:
    int X;
    Functor(int x) : X(x) {}
    int operator()(int y)
    {
        return X + y;
    }
};

template <typename T = void>
struct Greater
{
    [[nodiscard]] constexpr bool operator()(const T &left, const T &right)
    {
        return left > right;
    }
};

int main()
{
    std::vector<int> v1{1, 2, 3, 2, 3};
    std::vector<int> v2(v1.size());

    std::transform(v1.begin(), v1.end(), v2.begin(), Functor(2));
    for (auto &v2i : v2)
    {
        print(v2i);
    }
    LINE;

    std::sort(v1.begin(), v1.end(), std::greater<int>());
    for (auto &v1i : v1)
    {
        print(v1i);
    }
    LINE;

    std::sort(v2.begin(), v2.end(), Greater<int>());
    for (auto &v2i : v2)
    {
        print(v2i);
    }
    LINE;

    std::function<bool(const int &, const int &)> greater = [](const int &left, const int &right) -> bool
    { return left < right; };
    std::sort(v2.begin(), v2.end(), greater);
    for (auto &v2i : v2)
    {
        print(v2i);
    }
    LINE;

    auto last = std::unique(v2.begin(), v2.end());
    v2.erase(last, v2.end());
    for (auto &v2i : v2)
    {
        print(v2i);
    }
    LINE;
}
