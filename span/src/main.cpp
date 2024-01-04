#include <iostream>
#include <thread>
#include <string>
#include <future>
#include <vector>
#include <list>
#include <mutex>
#include <memory>
#include <span>
#include <array>

template <typename T>
void print(T &&t)
{
    std::cout << std::forward<T>(t) << std::endl;
}

// span - a view (i.e. non-owning) of a container providing bounds-checked access to a contigues group of elements. Since view do not own their elements they are cheap to construcand copy. A simplified way to think about views is they are holding references to their data. As opposed to maintaining a pointer/iterator and length field, a span wraps both of those up in a single object.

// Why you shouldn't pass std::string_view or std::span by reference:
//  They are essentially just pointers (and a size), so copying them is more efficient than passing a reference, especially considering the costs associated with dereferencing references
// Since they are non-owning, there's no issue with lifetime management. They don't own the data they point to, so you don't need to worry abouy the data being destroyed while the view is still in use.

// void printThreeInts(std::span<const int, 3> ints)

void printInts(std::span<const int> ints)
{
    for (const auto n : ints)
    {
        print(n);
    }
}

void printTwoInts(std::span<const int, 2> ints)
{
    for (const auto n : ints)
    {
        print(n);
    }
}

int main()
{
    std::vector v{1, 2, 3};
    std::array<int, 3> ar{1, 2, 3};
    int a[3] = {1, 2, 3};
    // printInts(v);
    // printInts(ar);
    // printInts(a);

    printTwoInts(std::span<const int, 2>{v.data(), 2});
    printTwoInts(std::span<const int, 2>{ar.data(), 2});
    printTwoInts(std::span<const int, 2>{a, 2});
}
