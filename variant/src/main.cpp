#include <iostream>
#include <thread>
#include <string>
#include <future>
#include <vector>
#include <list>
#include <mutex>
#include <cassert>
#include <variant>

template <typename T>
void print(T &&t)
{
    std::cout << t << std::endl;
}

// A union allocates enought memory to hold the largest member, and all members share that same memory space. This means that only one member of the union can be active at a time.
union Union
{
    int i;
    double d;
};

class Empty
{
};

int main()
{
    int i = 42;
    double d = 5.5;

    std::variant<int, double> v;
    v = i;
    v = d;
    if (auto value = std::get_if<double>(&v))
    {
        print(*value);
    }

    print(sizeof(v)); // 16 ??? 8 + 4 + 4???
    Empty e;
    print(sizeof(e)); // 1 //at least one byte for even empty data type
    std::variant<Empty> vEmpty;
    print(sizeof(vEmpty)); // 2 ???
    Union u;
    u.i = 1;
    print(sizeof(u)); // 8
    u.d = 2.0;
    print(sizeof(u)); // 8
    print(u.i);       // 0 //inactive
    print(u.d);       // 2
}
