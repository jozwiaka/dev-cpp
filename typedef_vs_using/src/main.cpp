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

template <typename T>
class Entity
{
public:
    using VectorT = std::vector<T>; // MODERN C++
    typedef std::vector<T> VectorT2;

private:
    VectorT v;
    VectorT2 v2;
};

int main()
{
    Entity<int> e;
    print("Success");
}
