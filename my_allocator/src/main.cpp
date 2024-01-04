#include <iostream>
#include <thread>
#include <string>
#include <future>
#include <vector>
#include <list>
#include <mutex>
#include <memory>

#include <cstdlib>
#include <limits>
#include <new>

template <typename T>
void print(T &&t)
{
    std::cout << std::forward<T>(t) << std::endl;
}

template <class T>
class Allocator
{
public:
    using value_type = T;

public:
    Allocator() = default;

    template <class U>
    constexpr Allocator(const Allocator<U> &) noexcept {}

    [[nodiscard]] T *allocate(std::size_t n)
    {
        if (n > std::numeric_limits<std::size_t>::max() / sizeof(T))
            throw std::bad_array_new_length();

        if (auto p = static_cast<T *>(std::malloc(n * sizeof(T))))
        {
            raport(p, n);
            return p;
        }

        throw std::bad_alloc();
    }

    void deallocate(T *p, std::size_t n) noexcept
    {
        raport(p, n, 0);
        std::free(p);
    }

    template <class U>
    bool operator==(const Allocator<U> &) { return true; }

    template <class U>
    bool operator!=(const Allocator<U> &) { return false; }

private:
    void raport(T *p, std::size_t n, bool alloc = true) const
    {
        std::cout << (alloc ? "Alloc: " : "Dealloc: ") << sizeof(T) * n << " bytes at " << std::hex << std::showbase << reinterpret_cast<void *>(p) << std::dec << '\n';
    }
};

int main()
{
    std::vector<int, ::Allocator<int>> v;
    v.push_back(1);
    v.push_back(2);
    v.push_back(2);
    v.push_back(2);
    v.push_back(2);
}
