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

void f(int &a)
{
    a++;
}

int main()
{
    auto a = 2;
    auto ref = std::ref(a);
    ref++;
    print(a);
    auto cref = std::cref(a); // const ref
                              // cref++; //error

    int i = 5;
    // std::thread t(f, i); error
    std::thread t(f, std::ref(i));
    t.join();
    std::cout << i << std::endl;
}
