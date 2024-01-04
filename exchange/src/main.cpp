#include <iostream>
#include <thread>
#include <string>
#include <future>
#include <vector>
#include <list>
#include <mutex>
#include <memory>
#include <utility>

template <typename T>
void print(T &&t)
{
    std::cout << std::forward<T>(t) << std::endl;
}

namespace Utility
{
    // U - default template argument
    template <class T, class U = T>
    constexpr T Exchange(T &obj, U &&newValue)
    {
        T oldValue = std::move(obj);
        obj = std::forward<U>(newValue);
        return oldValue;
    }
}

struct S
{
    int n;

    explicit S(int n = 0) : n{n} { std::cout << "S(int), n = " << n << std::endl; }
    explicit S(S &&other) noexcept : n{std::exchange(other.n, 0)}
    {
        std::cout << "S(S&&), n = " << n << std::endl;
    }
    S(const S &other) = delete;

    S &operator=(S &&other) noexcept
    {
        std::cout << "S &operator=(S &&), n = " << n << std::endl;
        if (this != &other)
        {
            n = std::exchange(other.n, 0);
        }
        return *this;
    }
    S &operator=(const S &other) = delete;
};

int main()
{

    // auto &&temp = S{1};
    // S s{std::move(temp)};

    S sConstructor{S{2}};
    S sMoveConstructor{std::move(S{2})};

    std::cout << "Success\n";
}
