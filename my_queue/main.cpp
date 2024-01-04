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

template <typename T>
void print(T &&t)
{
  std::cout << std::forward<T>(t) << std::endl;
}

template <typename T>
class Queue
{
public:
  void Push(const T &item)
  {
    print("Push item");
    std::unique_lock<std::mutex> lock(m_Mtx);
    m_Queue.push(item);
    lock.unlock();
    m_Cv.notify_one();
  }

  T Pop()
  {
    print("Pop item");
    std::unique_lock<std::mutex> lock(m_Mtx);
    m_Cv.wait(lock, [this]
              { return !m_Queue.empty(); });
    T frontItem = m_Queue.front();
    m_Queue.pop();
    return frontItem;
  }

private:
  std::mutex m_Mtx;
  std::condition_variable m_Cv;
  std::queue<T> m_Queue;
};

int main()
{
  print("OK");
  int *n = new int[5];
  delete[] n;
  auto result = std::async([]()
                           {
                            print("Thread");
                            return 1; });

  Queue<int> q;

  std::thread producer([&q]()
                       {
    for(int i = 0;i<5;++i)
    {
      q.Push(i);
      std::this_thread::sleep_for(std::chrono::milliseconds(100));
    } });

  std::thread consumer([&q]()
                       {
    for(int i=0;i<5;++i)
    {
      int item = q.Pop();
      print(item);
    } });

  producer.join();
  consumer.join();

  std::vector<int> v{1, 2, 3, 4};
  std::queue<int> queue;
  queue.push(1);
  queue.push(2);
  queue.push(3);
  queue.push(4);

  v.pop_back();
  print(v.back());
  queue.pop();
  print(queue.front());
}