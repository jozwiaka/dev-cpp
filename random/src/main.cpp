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
    // Use a random device to seed the random number generator
    std::random_device rd;

    // Use the Mersenne Twister engine for high-quality random nubmers
    std::mt19937 gen(rd());

    int min = 1;
    int max = 100;

    std::uniform_int_distribution<int> distribution(min, max);

    int randomNumber = distribution(gen);

    print(randomNumber);
}
