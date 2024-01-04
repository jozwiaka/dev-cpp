#include <iostream>
#include <thread>
#include <string>
#include <future>
#include <vector>
#include <list>
#include <mutex>
#include <format>

template <typename T>
void print(T &&t)
{
    std::cout << t << std::endl;
}

int main()
{
    std::string name = "JozwiakA";
    int age = 23;

    std::string output = std::format("name: {}; age: {}", name, age);
    print(output);
}
