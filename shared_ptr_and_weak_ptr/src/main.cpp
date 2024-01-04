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
    std::shared_ptr<int> p = std::make_shared<int>(1);
    int *i = new int(1);
    p.reset(i);
    print(p.use_count());
    // auto p2(p);
    // auto p3(p2);
    // p3 = p2;
    // p3.reset();
    // p3.reset();
    // p = std::make_shared<int>(2);
    // print(p.use_count());
    // print(p2.use_count());
    // int *n = new int(5);
    // delete[] n;
}
