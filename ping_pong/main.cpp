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
#include <chrono>

class PingPong
{
public:
    void start(size_t n)
    {
        bPingTurn = true;
        std::thread pingThread(&PingPong::ping, this, n);
        std::thread pongThread(&PingPong::pong, this, n);

        pingThread.join();
        pongThread.join();
    }

private:
    void ping(size_t n)
    {

        for (size_t i = n; --i;)
        {
            // std::this_thread::sleep_for(std::chrono::seconds(1));
            std::unique_lock<std::mutex> l(mtx);
            cv.wait(l, [this]()
                    { return bPingTurn; });
            std::cout << "Ping ";
            bPingTurn = false;
            cv.notify_one();
        }
    }

    void pong(size_t n)
    {
        for (size_t i = n; --i;)
        {
            std::unique_lock<std::mutex> l(mtx);
            cv.wait(l, [this]()
                    { return !bPingTurn; });
            std::cout << "Pong \n";
            bPingTurn = true;
            cv.notify_one();
        }
    }

private:
    bool bPingTurn = true;
    std::mutex mtx;
    std::condition_variable cv;
};

int main(int argc, char **argv)
{
    PingPong pingPong;
    pingPong.start(10);
}