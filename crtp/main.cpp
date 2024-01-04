#include <iostream>
#include <thread>
#include <string>
#include <future>
#include <vector>
#include <list>
#include <mutex>
#include <memory>
#include <functional>
#include <condition_variable>
#include <queue>

// CRTP = Curiously Recurring Template Pattern = technique where a class template inherits from its own template parameter. This pattern is often used to implement static polymporphism and can be see as a form of template-based inheritance.

template <typename Derived>
class Shape
{
public:
    void PrintArea() const
    {
        const auto &derived = static_cast<const Derived &>(*this);
        std::cout << "Shape:: " << derived.CalculateArea() << std::endl;
    }
};

class Rectangle : public Shape<Rectangle>
{
public:
    Rectangle(double a, double b) : a{a}, b{b} {}

    double CalculateArea() const
    {
        return a * b;
    }

private:
    double a;
    double b;
};

int main()
{
    Rectangle r{2.0, 3.0};
    r.PrintArea();
}