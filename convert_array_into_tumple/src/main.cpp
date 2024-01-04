#include <iostream>
#include <thread>
#include <string>
#include <future>
#include <vector>
#include <list>
#include <mutex>
#include <memory>
#include <tuple>
#include <array>

template <typename T>
void print(T &&t)
{
    std::cout << std::forward<T>(t) << std::endl;
}

template <typename Array, std::size_t... I>
decltype(auto) a2t_impl(const Array &a, std::integer_sequence<std::size_t, I...>)
{
    return std::make_tuple(a[I]...);
}

template <typename T, std::size_t N, typename Indices = std::make_index_sequence<N>>
decltype(auto) a2t(const std::array<T, N> &a)
{
    return a2t_impl(a, Indices());
}

int main()
{
    std::array<int, 3> a{1, 2, 3};
    auto t = a2t(a);
}
