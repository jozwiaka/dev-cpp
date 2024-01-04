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

// template <int N>
// struct Factorial
// {
//     enum
//     {
//         val = N * Factorial<N - 1>::val
//     };
// };

// template <>
// struct Factorial<0>
// {
//     enum
//     {
//         val = 1
//     };
// };

template <int N>
struct Factorial
{
    static constexpr int val = N * Factorial<N - 1>::val;

    // could be const but constexpr additionaly checks if it was done in compile time. The point is when the variable is static and we defining it, it needs to be const.
    // static const int val = N * Factorial<N - 1>::val; //Ok
};

template <>
struct Factorial<0>
{
    static constexpr int val = 1;

    // static const int val = 1; Ok
};

int main()
{
    constexpr int n = Factorial<3>::val;
    print(n);
}
