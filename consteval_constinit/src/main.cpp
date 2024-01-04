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

// Immediate function - indicates that a function must be evaluated at compile-time. This means that the function is required to produce a constant expression, and it will be executed during the compilation process rather than at runtime.
consteval int ceval(int n)
{
    return n;
}

constexpr int cexpr(int n)
{
    return n;
}

int main()
{
#define CONST_X 0
#if CONST_X
    const int x = 5; // constexpr int x = 5; //OK //const non lvalue reference variables are rvalues

    constexpr int a = ceval(x);
    constexpr int b = cexpr(x);
    const int a1 = ceval(x);
    const int b1 = cexpr(x);
    int a2 = ceval(x);
    int b2 = cexpr(x);
    static_assert(a);
    static_assert(a1);
    // static_assert(a2); //error non-constant expression
    static_assert(b);
    static_assert(b1);
    // static_assert(b2); //error - non-constant expression
    // constinit int i1 = x; // error - valid only for ix with static or thread storage duration
    // constinit int i2 = 1; // error - valid only for ix with static or thread storage duration
    static constinit int i1 = x;
    static constinit int i2 = 1;

#else
    int x = 5;

    // constexpr int a = ceval(x); // error
    // constexpr int b = cexpr(x); // error
    // const int a1 = ceval(x); // error
    const int b1 = cexpr(x);
    // int a2 = ceval(x); //error
    int b2 = cexpr(x);
    // static constinit int i1 = x; //error

    int y = 2;
    constexpr int g1 = 2;

#endif
    // ------------------------------------------------------------------------------------
    // ------------------------------------------------------------------------------------
    // constinit - requires that a variable must be initialized at compile-time

    auto g = [](int n)
    { return n; };

    constexpr auto gcexpr = [](int n)
    { return n; };

    constexpr auto f = [](bool b, auto g, int n)
    { return b ? 5 : g(n); };

    const int n = 1; // needs to be const
    static constinit int s = f(true, g, n);
    static constinit int d = f(false, g, n);
}
