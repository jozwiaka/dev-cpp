#include <iostream>
#include <thread>
#include <string>
#include <future>
#include <vector>
#include <list>
#include <mutex>
#include <memory>
#include <stop_token>
#include <condition_variable>
#include <queue>
#include <functional>
#include <tuple>

template <typename T>
void print(T &&t)
{
    std::cout << std::forward<T>(t) << std::endl;
}

class ThreadPool
{
public:
    explicit ThreadPool(std::size_t numThreads) : m_Stop(false)
    {
        m_Workers.reserve(numThreads);
        for (std::size_t i = 0; i < numThreads; ++i)
        {
            m_Workers.emplace_back([this]
                                   {
                while(true)
                {
                    std::function<void()> task;

                    {
                        std::unique_lock lock(m_QueueMutex);

                        while(!m_Stop && m_Tasks.empty())
                        {
                            std::cout<<"Idle... Waiting for a task to do"<<std::endl;
                            m_Condition.wait(lock);
                        }

                        if (m_Stop && m_Tasks.empty())
                        {
                            return;
                        }
                        
                        task = std::move(m_Tasks.front());
                        m_Tasks.pop();
                    }

                    task();
                } });
        }
    }

    template <typename F, typename... Args>
    auto Enqueue(F &&f, Args &&...args) -> std::future<std::invoke_result_t<F, Args...>>
    {
        using ReturnType = std::invoke_result_t<F, Args...>;

        // mutable is is used to allow modification of the captured variables
        auto task = std::make_shared<std::packaged_task<ReturnType()>>(
            [f = std::forward<F>(f), args = std::make_tuple(std::forward<Args>(args)...)]() mutable
            {
                // std::apply is specifically designed for calling functions with a tuple of arguments.

                // int result = std::invoke(foo, 42, "bar");
                // int result = std::apply(foo, std::make_tuple(42, "bar"));

                // invoke the callable object with the unpacked tuple of arguments
                return std::apply(std::move(f), std::move(args));
            });

        auto future = task->get_future();

        {
            std::unique_lock lock(m_QueueMutex);
            m_Tasks.emplace([task]()
                            {
                                // call lambda []()->ReturnType which calls "ReturnType f(Args... args)"
                                std::invoke(*task);
                                // (*task)(); //other way
                            });
        }

        m_Condition.notify_one();
        return future;
    }

    ~ThreadPool()
    {
        {
            std::unique_lock lock(m_QueueMutex);
            m_Stop = true;
        }

        m_Condition.notify_all();

        for (auto &worker : m_Workers)
        {
            worker.join();
        }
    }

private:
    std::vector<std::jthread> m_Workers;
    std::queue<std::function<void()>> m_Tasks;

    std::mutex m_QueueMutex;
    std::condition_variable m_Condition;
    bool m_Stop;
};

void Task(int id)
{
    std::this_thread::sleep_for(std::chrono::seconds(1));
    std::cout << "Task " << id << " executed by thread " << std::this_thread::get_id() << std::endl;
}

void LongTask(int id)
{
    std::this_thread::sleep_for(std::chrono::seconds(2));
    std::cout << "LongTask " << id << " executed by thread " << std::this_thread::get_id() << std::endl;
}

int main()
{
    ThreadPool pool(4);

    std::vector<std::future<void>> futures;

    for (int i = 1; i <= 16; ++i)
    {
        if (!(i % 4))
        {
            futures.emplace_back(pool.Enqueue(LongTask, i));
        }
        else
        {
            futures.emplace_back(pool.Enqueue(Task, i));
        }
    }

    for (auto &future : futures)
    {
        future.get();
    }

    // std::thread t(Task, 1);
    // std::jthread jt(Task, 2);
}
