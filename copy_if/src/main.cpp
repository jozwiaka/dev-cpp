#include <iostream>
#include <thread>
#include <string>
#include <future>
#include <vector>
#include <list>
#include <mutex>
#include <algorithm>

template <typename T>
void print(T &&t)
{
    std::cout << t << std::endl;
}

int main()
{
    std::vector<int> ns = {2, 4, 5, 3, 4};
    std::vector<int> evenNs;
    std::copy_if(ns.begin(), ns.end(), std::back_inserter(evenNs), [](int n)
                 { return n % 2 == 0; });

    std::for_each(evenNs.begin(), evenNs.end(), [](int n)
                  { print(n); });
}
