#include <iostream>
#include <thread>
#include <string>
#include <future>
#include <vector>
#include <list>
#include <mutex>
#include <memory>
#include <type_traits>

template <typename T>
void print(T &&t)
{
    std::cout << std::forward<T>(t) << std::endl;
}

// SFINAE = Substitution Failure Is Not An Error =

// Function template using SFINAE to check for the presence of the operator+
// template <typename T>
// concept Arithmetic = std::is_arithmetic<T>::value;

template <typename T>
concept Arithmetic = std::is_arithmetic_v<T>; // better

// Other type traits
// std::is_pointer_v
// std::is_class_v

template <typename T>
typename std::enable_if<std::is_arithmetic<T>::value, T>::type
add1(T a, T b)
{
    return a + b;
}

// returns void
template <typename T>
typename std::enable_if<std::is_arithmetic<T>::value, void>::type
add2(T a, T b)
{
    std::cout << a + b << std::endl;
}

template <Arithmetic T>
int add3(T a, T b)
{
    return a + b;
}

template <int I>
void div1(char (*)[I % 2 == 0] = nullptr)
{
    std::cout << "I is even\n";
}

template <int I>
void div1(char (*)[I % 2 == 1] = nullptr)
{
    std::cout << "I is odd\n";
}

template <int I>
void div2()
{
    if constexpr (I % 2 == 0)
    {
        std::cout << "I is even\n";
    }
    else
    {
        std::cout << "I is odd\n";
    }
}

int main()
{
    std::cout << add1(1, 2) << std::endl;

    // std::cout << add1("Hello", "World") << std::endl; // error: no type named ‘type’ in ‘struct std::enable_if<false, const char*>

    div1<0>();
    div1<1>();
    div2<0>();
    div2<1>();
}
