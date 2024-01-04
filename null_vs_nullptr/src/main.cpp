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

void f(char c) {}
void f(char *c) {}

int main()
{
    // f(NULL);    // error - ambiguous
    f(nullptr); // calls f(char*)
}
