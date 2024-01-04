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
    std::cout << t << std::endl;
}

struct A
{
    A(int &&n)
    {
        std::cout << "rvalue, n = " << n << "\n";
    }
    A(int &n)
    {
        std::cout << "lvalue, n = " << n << "\n";
    }
};

class B
{
public:
    template <class T1, class T2, class T3>
    B(T1 &&t1, T2 &&t2, T3 &&t3) : a1_{std::forward<T1>(t1)},
                                   a2_{std::forward<T2>(t2)},
                                   a3_{std::forward<T3>(t3)}
    {
    }

private:
    A a1_, a2_, a3_;
};

template <class T, class... U>
std::unique_ptr<T> make_unique(U &&...u)
{
    // Perfect forwarding.
    return std::unique_ptr<T>(new T(std::forward<U>(u)...));
}

template <class T>
auto make_unique_auto(auto &&...args)
{
    return std::unique_ptr<T>(new T(std::forward<decltype(args)>(args)...));
}

int main()
{
    print("A:");
    auto p1 = make_unique<A>(1); // rvalue
    int i = 2;
    auto p2 = make_unique<A>(i); // lvalue
    print("B:");
    auto t = make_unique_auto<B>(1, i, 3);
}
