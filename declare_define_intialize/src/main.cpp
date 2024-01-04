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

// Variables:
// int a; // definition
// a = 3; //initialization
// int a = 3; // definition + initialization
// extern int a; //declaration (in other translation unit)

// Functions:
// int f(int); //declaration
// int f(int a){return a} //definition

int main()
{
}
