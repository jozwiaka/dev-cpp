#include <iostream>
#include <thread>
#include <string>
#include <future>
#include <vector>
#include <list>
#include <mutex>

template <typename T>
void print(T &&t)
{
    std::cout << t << std::endl;
}

class Product
{
public:
    virtual void use() = 0;
    virtual ~Product() {}
};

class ProductA : public Product
{
public:
    void use() override
    {
        print("Use ProductA");
    }
};

class Creator
{
public:
    virtual std::unique_ptr<Product> createProduct() = 0;
    virtual ~Creator() {}
};

class CreatorA : public Creator
{
public:
    std::unique_ptr<Product> createProduct() override
    {
        return std::make_unique<ProductA>();
    }
};

int main()
{
    std::unique_ptr<Creator> creator = std::make_unique<CreatorA>();
    std::unique_ptr<Product> product = creator->createProduct();
    product->use();
}
