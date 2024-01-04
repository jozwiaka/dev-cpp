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

namespace Program
{
    namespace Version1
    {
        int getVersion() { return 1; }
        bool isFirstVersion() { return true; }
    }

    inline namespace Version2
    {
        int getVersion() { return 2; }
    }
}

#define NESTED_NAMESPACE 1
#ifdef NESTED_NAMESPACE

namespace A::B::C
{
    int i;
}
#else
namespace A
{
    namespace B
    {
        namespace B
        {
            int i;
        }
    }
}
#endif

void f()
{
    print("Global f()");
}
namespace Functions
{
    void f()
    {
        print("Functions::f()");
    }

    void test()
    {
        ::f(); // run global f()
    }

}

int main()
{
    print(Program::getVersion()); // 2
    // print(Program::isFirstVersion()); //error
    print(Program::Version1::getVersion());
    print(Program::Version2::getVersion());

    Functions::test();
}
