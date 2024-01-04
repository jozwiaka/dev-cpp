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

int main()
{
    float d1 = 3.14;
    int u1 = std::bit_cast<int>(d1); // safier way to reinterpret an object from one type to another
    print(d1);
    print(u1);

    float d2 = 3.14;
    int *u2 = reinterpret_cast<int *>(&d1);
    print(d2);
    print(*u2);
}
