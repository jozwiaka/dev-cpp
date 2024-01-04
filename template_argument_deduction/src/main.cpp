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

template <typename T = float>
struct Entity
{
    T Value;
    Entity() {}
    Entity(T val) : Value{val} {}
};

int main()
{
    Entity e1{1}; // Ok - Entity<int>
    Entity e2{};  // Ok - Entity<float>
}
