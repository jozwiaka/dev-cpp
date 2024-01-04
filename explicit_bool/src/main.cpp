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

struct Entity
{
    template <typename T>
    // if(arg == int)
    //  constructor = explicit
    explicit(std::is_integral_v<T>) Entity(T t)
    {
    }
};

int main()
{
    Entity e2 = "5"; // ok - non-explicit c'tor non-int
    // Entity e1 = 5;   // error - non-explicit c'tor int
    Entity e1{5}; // ok - explicit c'tor int
}
