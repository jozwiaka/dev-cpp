#include <iostream>
#include <thread>
#include <string>
#include <future>
#include <vector>
#include <list>
#include <mutex>
#include <utility>
#include <memory>

template <typename T>
void print(T &&t)
{
    std::cout << t << std::endl;
}

template <class T>
void universalReference(T &&i)
{
    i++;
}
void rvalueReference(int &&i)
{
    i++;
}
void lvalueReference(int &i)
{
    i++;
}

int main()
{
    int i = 1;
    // rvalueReference(i); #Error
    // print(i);
    universalReference(i);
    print(i);
    lvalueReference(i);
    print(i);
}
