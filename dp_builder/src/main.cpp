#include <iostream>
#include <thread>
#include <string>
#include <future>
#include <vector>
#include <list>
#include <mutex>
#include <memory>
#include <unordered_map>
#include <map>
#include <utility>

template <typename T>
void print(T &&t)
{
    std::cout << std::forward<T>(t) << std::endl;
}

class Product
{
public:
    void SetPart1(const std::string &part1)
    {
        m_Part1 = part1;
    }

    void SetPart2(const std::string &part2)
    {
        m_Part2 = part2;
    }

    void Show() const
    {
        std::cout << "Part1: " << m_Part1 << std::endl;
        std::cout << "Part2: " << m_Part2 << std::endl;
    }

private:
    std::string m_Part1;
    std::string m_Part2;
};

class ProductBuilder
{
public:
    ProductBuilder &WithPart1(const std::string &part1)
    {
        m_Product.SetPart1(part1);
        return *this;
    }

    ProductBuilder &WithPart2(const std::string &part2)
    {
        m_Product.SetPart2(part2);
        return *this;
    }

    operator Product() const
    {
        return m_Product;
    }

private:
    Product m_Product;
};

int main()
{
    Product product = ProductBuilder().WithPart1("Part A").WithPart2("Part B");

    product.Show();
}