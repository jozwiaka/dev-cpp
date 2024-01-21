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

class WrongEntity
{
public:
    int *Data;

public:
    // automatically generated rule of 5 - WRONG - if resource needs to be manually managed, we cannot rely on automatically generated rule of 5
};

class Entity
{
public:
    std::shared_ptr<int> Data;

public:
    // Entity &operator=(Entity &&) = delete; //once we delte or provide custom implementation of 1 of rule of 5 methods, all 5 default methods will be deleted
    // automatically generated rule of 5 - OK - rule of 0
};

int main()
{

    auto e = Entity();
    e.Data = std::make_shared<int>(2);
    auto e2(e);            // 1. Entity(const Entity&)
    auto e3(std::move(e)); // 3. //Entity(Entity&&)
    auto e4 = Entity();
    e4 = e3;            // 2. //Entity& operator=(const Entity&)
    e4 = std::move(e3); // 4. Entity& operator=(Entity&&)
    print(e4.Data.use_count());
} // 5. ~Entity()
