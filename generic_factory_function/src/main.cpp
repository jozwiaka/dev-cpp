#include <iostream>
#include <thread>
#include <string>
#include <future>
#include <vector>
#include <list>
#include <mutex>
#include <utility>
#include <memory>

template <typename T>
void print(T &&t)
{
    std::cout << t << std::endl;
}

class Product
{
public:
    virtual void print() const = 0;
    virtual ~Product() = default;
};

class ConcreteProduct : public Product
{
public:
    explicit ConcreteProduct(int i, double d) : m_i(i), m_d(d)
    {
    }

    void print() const override
    {
        std::cout << m_i << ", " << m_d << std::endl;
    }

private:
    int m_i;
    double m_d;
};

template <typename T, typename... Args>
std::unique_ptr<T> createProduct(Args &&...args)
{
    return std::make_unique<T>(std::forward<Args>(args)...);
}

int main()
{
    auto p = createProduct<ConcreteProduct>(2, 3.0);
    p->print();
}
