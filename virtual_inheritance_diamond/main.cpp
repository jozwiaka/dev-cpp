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

template <typename T>
void print(T &&t)
{
  std::cout << std::forward<T>(t) << std::endl;
}

class Interface
{
public:
  Interface() = default;
  virtual ~Interface() = default;

private:
  virtual void F1() = 0;
  virtual void F2() = 0;
};

class Derived1 : virtual public Interface // we do not need virtual keywords here, but it is a good practise (as override)
{
  void F1() override{};
};

class Derived2 : virtual public Interface // we do not need virtual keywords here, but it is a good practise (as override)
{
  void F2() override{};
};

// Diamond problem
class Full : public Derived1, public Derived2 // we do not need virtual keywords here, but it is a good practise (as override)
{
};

int main()
{
  Interface *i = new Full();
  delete i;
}