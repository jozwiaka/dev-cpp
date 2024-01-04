#include <iostream>

template <typename T1, typename T2>
void print(T1 &&arg1, T2 &&arg2)
{
    std::cout << std::forward<T1>(arg1) << ", " << std::forward<T2>(arg2) << std::endl;
}

int main()
{
// #define Distribution
#ifndef Distribution
#define LOG(x, y) print(x, y)
#else
#define LOG(x, y)
#endif

    LOG("Test", "Ok");
}
