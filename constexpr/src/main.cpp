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

// constexpr f() - constexpr specifier indicates that a f can be evaluated at compile-time
// const auto out - indicates that a variable's value cannot be modified after its initialization
constexpr const auto constexprSquare(auto x)
{
    return x * x;
}

auto normalSquare(auto x)
{
    return x * x;
}

template <typename Re, typename Im>
class Complex
{
public:
    constexpr Complex(Re re, Im im) : m_Re{re}, m_Im{im} {}
    constexpr double Real() { return m_Re; }
    constexpr double Imag() { return m_Im; }

private:
    Re m_Re;
    Im m_Im;
};

template <typename T>
constexpr bool isIntegral()
{
    // contexpr if
    if constexpr (std::is_integral<T>::value)
    {
        return true;
    }
    return false;
}

int main()
{

    constexpr auto a = constexprSquare(2); // mov DWORD PTR [rbp-4], 4

    auto b = normalSquare(2); // mov edi, 2
                              // call normalSquare(auto)
                              // mov DWORD PTR [rbp-8], eax\

    constexpr Complex c{1, 2.0};

    constexpr auto identity = [](auto n) constexpr
    { return n; };
    static_assert(identity(12) == 12);

    static_assert(isIntegral<int>() == true);
    static_assert(isIntegral<char>() == true);
    static_assert(isIntegral<double>() == false);

    constexpr auto f = [](auto n) constexpr
    { return std::is_constant_evaluated(); };
    constexpr auto g = [](auto n) consteval
    { return std::is_constant_evaluated(); };

    auto n = 10;
    const auto cn = 10;

    // constexpr variables must be initialized with constant expressions
    // constexpr functions can be evaluated at either compile-time or runtime, depending on context and the values of the arguments
    // constexpr auto f1 = f(n); //error - f(n) is not constant expression
    // constexpr auto g1 = g(n); //error - g(n) is not constant expression
    constexpr auto f2 = f(cn);
    constexpr auto g2 = g(cn);
    auto f3 = f(n);
    // auto g3 = g(n); //error
    auto f4 = f(cn);
    auto g4 = g(cn);

    print("f:");
    print(f(n));
    print(f(cn));
    print(f2);
    print(f3);
    print(f4);

    print("g:");
    print(g(cn));
    print(g2);
    print(g4);
}
