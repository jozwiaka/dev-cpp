#include <iostream>
#include <thread>
#include <string>
#include <future>
#include <vector>
#include <list>
#include <mutex>
#include <concepts>
#include <functional>

template <typename T>
void print(T &&t)
{
    std::cout << std::forward<T>(t) << std::endl;
}

// template <typename T>
// concept Concept = requires <Requirement>
// ...
// void f(Concept a){}

// template <typename T>
//     requires <Requirement>
// void f(T a){}

// template <typename T>
// concept Concept = requires <Requirement>
// ...
// template<typename T>
//     requires Concept<T>
// void f(T a){}

// template <typename T>
// std::enable_if_t<std::is_same_v<T, int>>
// f(T a) {}

// void f(std::same_as<int> auto a) {}

template <typename T>
concept IntegralType = std::is_integral<T>::value;

template <IntegralType T>
T square(T num)
{
    return num * num;
}

template <typename F, typename... Args>
concept Callable = requires(F &&f, Args &&...args) {
    std::invocable<F, Args...>;
    f(args...);
};

template <typename... Args, Callable<Args...> F>
void call(F &&f, Args &&...args)
{
    print(std::invoke(std::forward<F>(f), std::forward<Args>(args)...));
}

// C++14, SFINAE
template <typename T>
std::enable_if_t<std::is_same_v<T, int>>
f1(T x) {}

// C++20, concepts
void f2(std::same_as<int> auto x) {}

// // C++23, really
// void f3(really int x) {}

template <typename T>
concept HasNameAndSurname = requires(T v) {
    {
        v.name
    } -> std::convertible_to<std::string>;
    {
        v.surname
    } -> std::convertible_to<std::string>;
    {
        v.get()
    } -> std::convertible_to<std::tuple<std::string, std::string>>;
};

struct Person
{
    std::string name;
    std::string surname;
    std::tuple<std::string, std::string> get()
    {
        return {name, surname};
    }
};
struct Package
{
    std::string weight;
    std::string volume;
};

template <HasNameAndSurname Person>
struct IsPerson
{
    Person person;
};

int main()
{
    int a = 5;
    print(square(a));

    std::function<int(int, int)> f([](int a, int b) -> int
                                   {print("f(int, int)"); return a + b; });
    call(f, 5, 1);

    auto g = []()
    { print("g()"); return "Returns void"; };
    call(g);

    // f1(1.0); // error
    // f2(1.0); // error

    Package package;
    Person person;

    static_assert(HasNameAndSurname<Person>);
    // static_assert(HasNameAndSurname<Package>); // error

    IsPerson<Person> ip1;
    // IsPerson<Package> ip2; //error
}
