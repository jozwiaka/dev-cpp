#include <iostream>
#include <utility>

template <typename T>
struct SFINAEExample
{
    using ReferenceType = decltype(std::declval<T &>());
    using ValueType = decltype(std::declval<T>());
};

int main()
{

    int x = 5;
    const int &y = x;

    decltype(x) a = 10;
    decltype(y) b = a;

    SFINAEExample<int> example;

    // Use the types obtained with decltype
    using ReferenceType = typename SFINAEExample<int>::ReferenceType;
    using ValueType = typename SFINAEExample<int>::ValueType;

    std::cout << "Reference Type: " << typeid(ReferenceType).name() << std::endl;
    std::cout << "Value Type: " << typeid(ValueType).name() << std::endl;

    return 0;
}
