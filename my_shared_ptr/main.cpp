#include <iostream>
#include <memory>

class RefCount
{
public:
    constexpr RefCount() noexcept = default;
    RefCount(const RefCount &) = delete;
    RefCount &operator=(const RefCount &) = delete;
    ~RefCount() noexcept = default;

    long UseCount() const noexcept
    {
        return m_Uses;
    }

    void Incref() noexcept
    {
        ++m_Uses;
    }

    void Decref() noexcept
    {
        --m_Uses;
    }

private:
    long m_Uses = 1;
};

template <typename T>
class SharedPtr
{
public:
    using ValueType = T;
    using PointerType = T *;

public:
    constexpr SharedPtr() noexcept = default;

    constexpr SharedPtr(nullptr_t) noexcept {};

    explicit SharedPtr(PointerType ptr) : m_Ptr{ptr},
                                          m_Count{new RefCount()}
    {
    }

    SharedPtr(const SharedPtr &other) noexcept
    {
        CopyConstructFrom(other);
    }

    SharedPtr(SharedPtr &&other) noexcept
    {
        std::cout << "Move constructor\n";
        MoveConstructFrom(std::move(other));
    }

    ~SharedPtr() noexcept
    {
        Decref();
    }

    SharedPtr &operator=(const SharedPtr &other) noexcept
    {
        SharedPtr(other).Swap(*this);
        return *this;
    }

    SharedPtr &operator=(SharedPtr &&other) noexcept
    {
        std::cout << "Move =\n";
        SharedPtr(std::move(other)).Swap(*this);
        return *this;
    }

    PointerType
    operator->() const noexcept
    {
        return m_Ptr;
    }

    explicit operator bool() const noexcept
    {
        return m_Ptr != nullptr;
    }

    ValueType &operator*() const noexcept
    {
        return *m_Ptr;
    }

    long UseCount() const noexcept
    {
        return m_Count ? m_Count->UseCount() : 0;
    }

    void Reset() noexcept
    {
        SharedPtr().Swap(*this);
    }

    void Reset(PointerType ptr)
    {
        SharedPtr(ptr).Swap(*this);

        // auto temp = SharedPtr(ptr);
        // temp.Incref();
        // temp.Swap(*this);
    }

    PointerType Get() const noexcept
    {
        return m_Ptr;
    }

private:
    void Swap(SharedPtr &other) noexcept
    {
        std::swap(m_Ptr, other.m_Ptr);
        std::swap(m_Count, other.m_Count);
    }

    void CopyConstructFrom(const SharedPtr &other) noexcept
    {
        if (other.m_Count)
        {
            other.Incref();
            m_Ptr = other.m_Ptr;
            m_Count = other.m_Count;
        }
    }

    void MoveConstructFrom(SharedPtr &&other) noexcept
    {
        m_Ptr = std::exchange(other.m_Ptr, nullptr);
        m_Count = std::exchange(other.m_Count, nullptr);
    }

    void Incref() const noexcept
    {
        if (m_Count)
        {
            m_Count->Incref();
        }
    }

    void Decref() noexcept
    {
        if (m_Count)
        {
            std::cout << "[&sharedPtr = " << this << "]: Decref: " << m_Count->UseCount() << "\n";
            m_Count->Decref();
            if (m_Count->UseCount() == 0)
            {
                // std::cout << "[" << this << "]: Decref: " << m_Count->UseCount() << "\n";
                delete m_Count;
                if (m_Ptr)
                {
                    delete m_Ptr;
                    m_Ptr = nullptr;
                }
            }
        }
    }

private:
    PointerType m_Ptr{nullptr};
    RefCount *m_Count{nullptr};
};

class bar
{
    int i;

public:
    explicit bar(int p) : i(p) { std::cout << "bar() " << this << std::endl; }
    ~bar() { std::cout << "~bar() " << this << std::endl; }
    void foo() const
    {
        std::cout << "foo() " << this << " i = " << i << std::endl;
    }
};

int main(int, char **)
{
    std::cout << "### p1 ###\n";
    SharedPtr<bar> p1(new bar(10));
    if (p1)
        p1->foo();

    {
        std::cout << "### p2 ###\n";
        SharedPtr<bar> p2 = p1;
        if (p2)
            p2->foo();
    }

    {
        std::cout << "### p3 ###\n";
        SharedPtr<bar> p3(new bar(20));
        p3 = p1;
        if (p3)
            p3->foo();
    }

    {
        std::cout << "### p4 ###\n";
        SharedPtr<bar> p4;
        p4 = p1;
        if (p4)
            p4->foo();
    }

    {
        bar o = *p1;
        o.foo();
    }

    std::cout << "### MOVE START###\n";
    SharedPtr<bar> ptrMove{std::move(SharedPtr<bar>{new bar(1)})};

    SharedPtr<bar> ptrMove2;
    ptrMove2 = std::move(SharedPtr<bar>{new bar(1)});
    std::cout << "### MOVE END###\n";

    SharedPtr<bar> ptr1{new bar(1)};
    std::cout << "[ptr = " << ptr1.Get() << "]: " << ptr1.UseCount() << std::endl;
    SharedPtr<bar> ptr11{ptr1};
    SharedPtr<bar> ptr12;
    ptr12 = ptr1;

    SharedPtr<bar> ptr2{new bar(2)};
    std::cout << "Reset:\n";
    // ptr1.Reset(); //Ok
    // ptr2.Reset(new bar(2)); // Ok

    std::cout << "[&sharedPtr = " << &ptr1 << "]"
              << "[ptr = " << ptr1.Get() << "]: " << ptr1.UseCount() << std::endl;
    std::cout << "[&sharedPtr = " << &ptr2 << "]"
              << "[ptr = " << ptr2.Get() << "]: " << ptr2.UseCount() << std::endl;

    std::cout << "END OF SCOPE\n";
    return 0;
}
