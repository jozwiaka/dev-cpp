#include <iostream>
#include <thread>
#include <string>
#include <future>
#include <vector>
#include <list>
#include <mutex>

template <typename T>
void print(T &&t)
{
    std::cout << t << std::endl;
}

int main()
{
    int *p1 = new int;
    delete p1;

    int *p2 = static_cast<int *>(::operator new(sizeof(int)));
    ::operator delete(p2);
}
