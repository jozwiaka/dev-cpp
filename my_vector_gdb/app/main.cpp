#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include "Vector.hpp"

template <typename T>
void print(T &&t)
{
    std::cout << std::forward<T>(t) << std::endl;
}
struct Vector2
{
    float x = 0.0f, y = 0.0f;
    int *m_memoryBlock;
    Vector2()
    {
        print("Default constructor");
        m_memoryBlock = new int[5];
    }
    Vector2(float scalar) : x(scalar), y(scalar)
    {
        m_memoryBlock = new int[5];
    }
    Vector2(float x, float y) : x(x), y(y)
    {
        m_memoryBlock = new int[5];
    }
    Vector2(const Vector2 &other) = delete;
    Vector2(Vector2 &&other) : x(other.x), y(other.y)
    {
        m_memoryBlock = other.m_memoryBlock;
        other.m_memoryBlock = nullptr;
        print("Move constructor");
    }
    ~Vector2()
    {
        delete[] m_memoryBlock;
        print("Destroy");
    }
    Vector2 &operator=(const Vector2 &other) = delete;
    Vector2 &operator=(Vector2 &&other)
    {
        if (this != &other)
        {
            x = std::exchange(other.x, 0);
            y = std::exchange(other.y, 0);
            // delete old data
            delete[] m_memoryBlock;
            m_memoryBlock = std::exchange(other.m_memoryBlock, nullptr);
        }
        print("Move = ");
        return *this;
    }
};

template <typename T>
void printVector(const Vector<T> &strings)
{
    for (size_t i = 0; i < strings.size(); i++)
    {
        print(strings[i]);
    }
}

template <>
void printVector(const Vector<Vector2> &strings)
{
    for (size_t i = 0; i < strings.size(); i++)
    {
        std::string buff;
        buff += std::to_string(strings[i].x);
        buff += ", ";
        buff += std::to_string(strings[i].y);
        print(buff);
    }
}

int main()
{
    Vector<Vector2> vectors2;
    vectors2.emplaceBack(1);
    vectors2.emplaceBack(2);
    vectors2.emplaceBack(3);
    vectors2.popBack();
    vectors2.emplaceBack(3);
    printVector(vectors2);
    print("------------------------------");

    Vector<std::string> strings;
    strings.emplaceBack("a");
    strings.emplaceBack("b");
    strings.emplaceBack("c");
    strings.popBack();
    strings.emplaceBack("c");
    printVector(strings);
    print("------------------------------");

    for (const auto &string : strings)
    {
        print(string);
    }
    print("------------------------------");

    for (Vector<std::string>::Iterator it = strings.begin(); it != strings.end(); it++)
    {
        print(*it);
    }
    print("------------------------------");

    auto it = strings.begin();
    print(*(++it)); // b
    print(*(it++)); // b
    print(*(it));   // c
    print(it[0]);   // c
    print("------------------------------");
}
