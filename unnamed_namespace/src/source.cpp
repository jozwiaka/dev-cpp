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

// prefer unnamed namespaces than static, because:
//  1. possibility of creating internal linkage class, where creatic static class is impossible to do
//  2. consistance with the std library programming style
//  3. cleaner code - do not need to type 'static' entire time
//  4. optimize the code - internal linkage is less costly than external one
namespace
{
    int a; // internal linkage

    class Entity // internal linkage
    {
    };
}

const int b = 2; // internal linkage

int c = 3; // external linkage

static int d = 4; // internal linkage

int main()
{
}
