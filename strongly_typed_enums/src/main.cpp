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

// Specifying underlying type as unsigned int
enum class Color : unsigned int
{
    Red = 0xff0000,
    Green = 0xff00,
    Blue = 0xff
};

// Red / Green in Alert don't conflict with Color
enum class Alert : bool
{
    Red,
    Green
};

int main()
{
    Color c = Color::Red;
}
