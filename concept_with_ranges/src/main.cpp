#include <iostream>
#include <vector>
#include <ranges>
#include <set>

template <typename T>
void print(T &&t)
{
    std::cout << t << std::endl;
}

template <std::ranges::range Range>
void printRange(const Range &range)
{
    for (const auto &item : range)
    {
        print(item);
    }
}

int main()
{
    std::set<int> ns = {2, 4, 6, 4}; // 2, 4, 6 //4 will be eliminated because is duplicated
    printRange(ns);

    std::string str = "Concepts with ranges";
    printRange(str); // print letters one by one
}
