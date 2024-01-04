#include <iostream>
#include <thread>
#include <string>
#include <future>
#include <vector>
#include <list>
#include <mutex>
#include <optional>

std::optional<int> divide(int a, int b)
{
    if (b != 0)
        return a / b;
    else
        return std::nullopt; // Indicate that the result is not available
}

int main()
{
    auto result = divide(6, 3);
    if (result)
    {
        std::cout << *result << std::endl;
    }
}
