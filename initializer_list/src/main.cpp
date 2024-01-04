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

class Entity
{
public:
    Entity() { std::cout << "Default constructor\n"; }
    Entity(int x) { std::cout << "Parametrized constructor: " << x << std::endl; }
};

struct Point
{
    int x, y;
};

class Empty
{
};

int main()
{
    Empty em1;           // calls the default contructor
    Empty em2();         // AMBIGUITY!!! // declares the function named em2
    Empty em3{};         // calls the default contructor
    Empty em4 = Empty(); // calls the default contructor

    Entity e1{};          // calls the default contructor
    Entity e2();          // AMBIGUITY!!! // declares the function named e2
    Entity e3;            // calls the default contructor
    Entity e4 = Entity(); // calls the default contructor - do this explicitly instead of Entity e2();
    Entity e5(1);         // calls the parametrized contructor - works in the same way
    Entity e6{1};         // calls the parametrized contructor - works in the same way
    // USE {} INSTEAD OF OLDER SYNTAX () TO AMBIGUITY

    Point p1 = {1, 2}; // aggregate initialization
    Point p2{1, 2};    // uniform initialization //BETTER - MORE MODERN //older compilers (older than C++11) may throw error

    int x = 4.5; // no error
    // int y{4.5};  // error - narrowing conversion //BETTER

    std::initializer_list<int> numbers = {1, 2, 3};
    std::vector<int> v1 = {1, 2, 3}; // copy-list initlization - it may involve an extra copy operation and is less explicit
    std::vector<int> v2{1, 2, 3};    // THE BEST
    std::vector<int> v3(numbers);    // directly accepts an std::initializer_list as an argument of the constructor
    std::vector<int> v4{numbers};    // THE BEST //uses a copy-list-initialization to create a new std::vector by copying the values from the std::initializer_list
    std::vector<int> v5 = numbers;   // this form involves a copy of the std::initializer_list which might not be as efficient as using brace-enclosed initliazers directly

    // auto x1{1, 2, 3}; //error - not a single element
    auto x2 = {1, 2, 3}; // std::<initializer_list<int>
}
