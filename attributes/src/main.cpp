#include <iostream>
#include <thread>
#include <string>
#include <future>
#include <vector>
#include <list>
#include <mutex>
#include <memory>

template <typename T>
void print(T &&t)
{
    std::cout << std::forward<T>(t) << std::endl;
}

[[noreturn]] void f() { throw "error"; }
[[deprecated]] void legacyF1() {}
[[deprecated("reason")]] void legacyF2() {}
[[maybe_unused]] void legacyF() {}
[[randomText]] void test() {} // warning - no such attribute directive

int main()
{
    f();
    switch (1)
    {
    case 1:
        [[fallthrough]];
    case 2:
        break;
    case 3:
        [[fallthrough]];
    default:
        break;
    }
}
