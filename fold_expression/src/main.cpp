#include <iostream>

template <typename T>
void print(T &&t)
{
    std::cout << t << std::endl;
}

template <typename... Args>
auto sum(Args... args)
{
    return (args + ...);
}

template <typename... Args>
auto validate(Args... args)
{
    return (args && ...);
}

int main()
{
    auto total = sum(1.0, 2.0f, 3); // double, float, int
    print(total);

    print(validate(true, 1, 2));  // 1
    print(validate(false, 1, 2)); // 0
    print(validate(true, 0, 2));  // 0
}
