#include <iostream>
#include <thread>
#include <string>
#include <future>
#include <vector>
#include <list>
#include <mutex>
#include <memory>

template <typename T>
void print(T &&t)
{
    std::cout << std::forward<T>(t) << std::endl;
}

class Subject
{
public:
    virtual void Request() const = 0;
    virtual ~Subject() = default;
};

class SubjectA : public Subject
{
public:
    SubjectA() = default;
    SubjectA(const std::string &name) : m_Name{name} {}

    void Request() const override
    {
        std::cout << "SubjectA::Request(), m_Name: " << m_Name << std::endl;
    }

private:
    std::string m_Name;
};

class ProxySubjectA : public SubjectA
{
public:
    ProxySubjectA(const std::string &name) : m_SubjectA{std::make_unique<SubjectA>(name)} {}

    void Request() const override
    {
        m_SubjectA->Request();
    }

private:
    std::unique_ptr<SubjectA> m_SubjectA;
};

int main()
{
    std::unique_ptr<SubjectA> subjectA = std::make_unique<ProxySubjectA>("Test");
    subjectA->Request();
}
