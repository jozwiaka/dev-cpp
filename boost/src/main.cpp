#include <iostream>
#include <thread>
#include <string>
#include <future>
#include <vector>
#include <list>
#include <mutex>
#include <boost/filesystem.hpp>

template <typename T>
void print(T &&t)
{
    std::cout << std::forward<T>(t) << std::endl;
}

int main()
{
    boost::filesystem::path path("../src/test_folder");

    if (boost::filesystem::is_directory(path))
    {
        print("Dir exists");
    }
    else
    {
        print("Dir does not exists");
    }
}
