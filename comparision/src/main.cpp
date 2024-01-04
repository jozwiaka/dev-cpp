#include <iostream>
#include <thread>
#include <string>
#include <future>
#include <vector>
#include <list>
#include <mutex>
#include <compare>

template <typename T>
void print(T &&t)
{
    std::cout << t << std::endl;
}

struct Point
{
    int x;

    auto operator<=>(const Point &other) const = default;
};

int main()
{
    Point p1{2};
    Point p2{2};

    auto result = p1 <=> p2; // ok
    auto result2 = 1 <=> 2;  // ok

    if (result < 0)
        std::cout << "p1 is less than p2\n";
    else if (result > 0)
        std::cout << "p1 is greater than p2\n";
    else
        std::cout << "p1 and p2 are equal\n";
}
