#include <iostream>
#include <thread>
#include <mutex>

std::mutex mutex1;
std::mutex mutex2;

void function1()
{
    std::cout << "Thread 1: Trying to lock mutex1..." << std::endl;
    std::unique_lock<std::mutex> lock1(mutex1);
    std::this_thread::sleep_for(std::chrono::milliseconds(1)); // Simulate some work
    std::cout << "Thread 1: Locked mutex1." << std::endl;

    std::cout << "Thread 1: Trying to lock mutex2..." << std::endl;
    std::unique_lock<std::mutex> lock2(mutex2);
    std::cout << "Thread 1: Locked mutex2." << std::endl;

    // Do some work with the locked resources...

    lock2.unlock();
    lock1.unlock();
}

void function2()
{
    std::cout << "Thread 2: Trying to lock mutex2..." << std::endl;
    std::unique_lock<std::mutex> lock2(mutex2);
    std::this_thread::sleep_for(std::chrono::milliseconds(1)); // Simulate some work
    std::cout << "Thread 2: Locked mutex2." << std::endl;

    std::cout << "Thread 2: Trying to lock mutex1..." << std::endl;
    std::unique_lock<std::mutex> lock1(mutex1);
    std::cout << "Thread 2: Locked mutex1." << std::endl;

    // Do some work with the locked resources...

    lock1.unlock();
    lock2.unlock();
}

int main()
{
    std::thread t1(function1);
    std::thread t2(function2);

    t1.join();
    t2.join();

    return 0;
}
