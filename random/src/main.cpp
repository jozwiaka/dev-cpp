#include <iostream>
#include <thread>
#include <string>
#include <future>
#include <vector>
#include <list>
#include <mutex>
#include <memory>
#include <random>

template <typename T>
void print(T &&t)
{
    std::cout << std::forward<T>(t) << std::endl;
}

int main()
{
    for (int i = 0; i < 10; i++)
    {
        // Use a random device to seed the random number generator
        static std::random_device rd;

        // Use the Mersenne Twister engine for high-quality random nubmers
        static std::mt19937 gen(rd());

        int min = 1;
        int max = 100;

        static std::uniform_int_distribution<int> distribution(min, max);

        int randomNumber = distribution(gen);

        print(randomNumber);
    }
}
