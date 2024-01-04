#include <iostream>
#include <thread>
#include <string>
#include <future>
#include <vector>
#include <list>
#include <mutex>
#include <memory>
#include <functional>
#include <unordered_map>

template <typename T>
void print(T &&t)
{
    std::cout << std::forward<T>(t) << std::endl;
}

class EventManager
{
public:
    using Callback = std::function<void()>;

public:
    void RegisterEvent(const std::string &eventName, Callback callback)
    {
        m_Callbacks[eventName].push_back(callback);
    }

    void TriggerEvent(const std::string &eventName)
    {
        auto eventCallbacks = m_Callbacks.find(eventName);
        if (eventCallbacks != m_Callbacks.end())
        {
            for (const auto &callback : eventCallbacks->second)
            {
                callback();
            }
        }
        else
        {
            std::cout << "Event '" << eventName << "' has no callbacks registered.\n";
        }
    }

private:
    std::unordered_map<std::string, std::vector<Callback>> m_Callbacks;
};

int main()
{
    EventManager eventManager;

    eventManager.RegisterEvent("start", []()
                               { std::cout << "App started\n"; });
    eventManager.RegisterEvent("end", []()
                               { std::cout << "App ended\n"; });

    eventManager.TriggerEvent("start");
    eventManager.TriggerEvent("unregistered event name");
    eventManager.TriggerEvent("end");
}
