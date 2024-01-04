#include <iostream>
#include <thread>
#include <string>
#include <future>
#include <vector>
#include <list>
#include <mutex>
#include <memory>
#include <gtest/gtest.h>

template <typename T>
void print(T &&t)
{
    std::cout << std::forward<T>(t) << std::endl;
}

TEST(MathTest, Addition)
{
    EXPECT_EQ(2 + 2, 4);
}

TEST(MyDeathTest, ExpectsDeath)
{
    EXPECT_DEATH(
        {
            std::abort();
        },
        ".*");
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
