#include <iostream>
#include <thread>
#include <string>
#include <future>
#include <vector>
#include <list>
#include <mutex>
#include <atomic>

template <typename T>
void print(T &&t)
{
    std::cout << t << std::endl;
}

// function to be executed by multiple threads
void incrementCounter(std::atomic<int> &counter, int iterations)
{
    for (int i = 0; i < iterations; ++i)
    {
        counter.fetch_add(1, std::memory_order_relaxed);
    }
}

int main()
{
    const int numThreads = 4;
    const int iterationsPerThread = 100000;

    std::atomic<int> counter(0);

    std::thread threads[numThreads];

    for (int i = 0; i < numThreads; i++)
    {
        threads[i] = std::thread(incrementCounter, std::ref(counter), iterationsPerThread);
    }

    for (int i = 0; i < numThreads; i++)
    {
        threads[i].join();
    }

    print(counter);
}
