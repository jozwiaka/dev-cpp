#include <iostream>
#include <thread>
#include <string>
#include <future>
#include <vector>
#include <list>
#include <mutex>
#include <memory>
#include <functional>

template <typename T>
void print(T &&t)
{
    std::cout << std::forward<T>(t) << std::endl;
}

template <typename Callable>
class Proxy
{
public:
    Proxy(Callable callable) : m_Callable(std::move(callable)) {}

    template <typename... Args>
    auto operator()(Args &&...args)
    {
        return std::invoke(m_Callable, std::forward<Args>(args)...);
    }

private:
    Callable m_Callable;
};

int main()
{
    const auto add = [](int x, int y)
    { return x + y; };

    Proxy p{add};
    print(p(1, 2));
}
