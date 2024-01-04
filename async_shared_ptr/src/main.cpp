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
    Entity(int data) : m_Data(data) {}

    void ProcessData()
    {
        std::cout << "Processing data: " << m_Data << std::endl;
    }

private:
    int m_Data;
};

int main()
{
    auto sharedObject = std::make_shared<Entity>(5);
    std::future<void> futureResult = std::async(std::launch::async, [sharedObject]()
                                                {   
                                                    std::cout<<"[TASK]: Reference count = "<<sharedObject.use_count()<<std::endl;
                                                    sharedObject->ProcessData(); });

    futureResult.get();
    std::cout << "[MAIN]: Reference count = " << sharedObject.use_count() << std::endl;
}
