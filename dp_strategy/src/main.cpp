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

class Strategy
{
public:
    virtual void execute() = 0;
    virtual ~Strategy() {}
};

class StrategyA : public Strategy
{
public:
    void execute() override
    {
        print("Executing StrategyA");
    }
};

class Context
{
private:
    std::unique_ptr<Strategy> strategy;

public:
    void setStrategy(std::unique_ptr<Strategy> s)
    {
        strategy = std::move(s);
    }

    void executeStrategy()
    {
        if (strategy)
        {
            strategy->execute();
        }
    }
};

int main()
{
    Context context;
    context.setStrategy(std::make_unique<StrategyA>());
    context.executeStrategy();

    // change strategy
    //  context.setStrategy(std::make_unique<StrategyB>());
    //  context.executeStrategy();
}
