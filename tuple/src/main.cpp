#include <iostream>
#include <thread>
#include <string>
#include <future>
#include <vector>
#include <list>
#include <mutex>
#include <memory>
#include <tuple>

template <typename T>
void print(T &&t)
{
    std::cout << std::forward<T>(t) << std::endl;
}

std::tuple<std::string, int> createPerson()
{
    // return {"Name", 23};
    return std::make_tuple("Name", 23);
}

int main()
{
    std::vector<std::tuple<std::string, int>> v{createPerson()};
    for (const auto &[name, age] : v)
    {
        print(name);
        print(age);
    }
}
