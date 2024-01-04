#include <iostream>
#include <thread>
#include <string>
#include <future>
#include <vector>
#include <list>
#include <mutex>
#include <memory>
#include <stack>
#include <queue>

template <typename T>
void print(T &&t)
{
    std::cout << std::forward<T>(t) << std::endl;
}

// queue - FIFO
// OUT
// 1 <- out
// 2
// 3
// 4 <- in
// IN

// stack - LIFO
// OUT
// 4 <- out <- in
// 3
// 2
// 1
// IN

int main()
{
    std::string s;
    // Using std::queue
    std::queue<int> myQueue;

    myQueue.push(1);
    myQueue.push(2);
    myQueue.push(3);

    std::cout << "Queue elements (FIFO): ";
    while (!myQueue.empty())
    {
        std::cout << myQueue.front() << " ";
        myQueue.pop();
    }
    std::cout << "\n\n";

    // Using std::stack
    std::stack<int> myStack;

    myStack.push(1);
    myStack.push(2);
    myStack.push(3);

    std::cout << "Stack elements (LIFO): ";
    while (!myStack.empty())
    {
        std::cout << myStack.top() << " ";
        myStack.pop();
    }
    std::cout << "\n";

    return 0;
}