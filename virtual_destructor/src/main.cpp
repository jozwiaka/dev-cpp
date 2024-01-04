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

class Shape
{
public:
    virtual ~Shape() { print("~Shape()"); };
    // Shape(const Shape &) = delete; //deleted copy constructor
    // Shape &operator=(const Shape &) = delete; //deleted assignment operator
    virtual double Area() = 0;

protected:
    double a;
    double h;
    Shape(double a, double h) : a{a}, h{h} {};
};

class Rectangle : public Shape
{
public:
    Rectangle(double a, double b) : Shape(a, b) {}
    double Area() override
    {
        std::cout << "Rectangle::Area(), this = " << this << std::endl;
        return a * h;
    }
    virtual ~Rectangle() override { print("~Rectangle()"); };
};

class Square : public Rectangle
{
public:
    Square(double a) : Rectangle(a, a) {}
    double Area() override
    {
        std::cout << "Square::Area(), this = " << this << std::endl;
        return a * h;
    }
    virtual ~Square() override { print("~Square()"); };
};

int main()
{
    Rectangle rectangle(2, 5);
    Square square(10);
    std::cout << "&rectangle = " << &rectangle << std::endl;
    std::cout << "&square = " << &square << std::endl;

    print("\n### shape = square; ###");
    Shape &shape{rectangle};
    print(shape.Area()); // 10
    shape = square;      // Shape::operator= -> assign square vars values to rectangle vars values: rectangle.x = square.x; shape still points to Rectangle's overriden function pointers in vtable
    print(shape.Area()); // 100

    print("\n### *pShape = square; ###");
    Shape *pShape{&rectangle};
    print(pShape->Area()); // 100 //(prev) because rectangle.x = square.x
    *pShape = square;
    print(pShape->Area()); // 100

    print("\n### pShape = &square; ###");
    Shape *pShape2{&rectangle};
    print(pShape2->Area()); // 100 //(prev) because rectangle.x = square.x
    pShape2 = &square;      // already pShape points to Square in vtable
    print(pShape2->Area()); // 100

    print("\nDestroy the square and, then next destroy the rectangle:");
    // Destroy square (at first)
    // ~Square()
    // ~Rectangle()
    // ~Shape()

    // Destroy rectangle
    // ~Rectangle()
    // ~Shape()
}
