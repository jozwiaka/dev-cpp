#include <iostream>

// To make it obvious that we are in suppose to take a Vector type
template <typename Vector>
class VectorIterator
{
public:
    using ValueType = typename Vector::ValueType; // typename seems optional here
    using PointerType = ValueType *;
    using ReferenceType = ValueType &;

public:
    VectorIterator(PointerType ptr) : m_ptr(ptr) {}

    // ++i - Prefix operator
    VectorIterator &operator++()
    {
        ++m_ptr;
        return *this;
    }

    // i++ - Postfix operator - we do not want to modify the object in place
    VectorIterator operator++(int)
    {
        VectorIterator iterator = *this;
        ++(*this);
        return iterator;
    }

    VectorIterator &operator--()
    {
        --m_ptr;
        return *this;
    }

    VectorIterator operator--(int)
    {
        VectorIterator iterator = *this;
        --(*this);
        return iterator;
    }

    ReferenceType operator[](int index)
    {
        return *(m_ptr + index);
        // other way:
        // return m_ptr[index];
    }

    PointerType operator->()
    {
        return m_ptr;
    }

    ReferenceType operator*()
    {
        return *m_ptr;
    }

    bool operator==(const VectorIterator &other) const
    {
        return m_ptr == other.m_ptr;
    }

    bool operator!=(const VectorIterator &other) const
    {
        return m_ptr != other.m_ptr;
    }

private:
    PointerType m_ptr;
};

template <typename T>
class Vector
{
public:
    using ValueType = T;
    using Iterator = VectorIterator<Vector<T>>;

public:
    Vector()
    {
        reAllocate(2);
    }

    ~Vector()
    {
        // call destructors of T
        clear();

        // this will call destructors of T
        //  delete[] m_data;

        //  we want only to delete the memory
        ::operator delete(m_data, m_capacity * sizeof(T));
    }

    void pushBack(const T &value)
    {

        if (m_size >= m_capacity)
        {
            reAllocate(m_capacity + m_capacity / 2);
        }

        m_data[m_size] = value;
        m_size++;
    }

    void pushBack(T &&value)
    {
        if (m_size >= m_capacity)
        {
            reAllocate(m_capacity + m_capacity / 2);
        }
        m_data[m_size] = std::move(value);
        m_size++;
        // destroy T value temporary object at the end of scope
    }

    template <typename... Args>
    T &emplaceBack(Args &&...args)
    {
        if (m_size >= m_capacity)
        {
            reAllocate(m_capacity + m_capacity / 2);
        }

#if 1 // IMPROVEMENT:
      // Construct data element in place T(Args...) - in the address of &m_data[m_size]
        new (&m_data[m_size]) T(std::forward<Args>(args)...);
#else // BAD PRACTISE - DESTROY TEMP AFTER (MOVE) ASSIGNMENT:
      //  1. construct temp T(std::forward<Args>(args)...)
      //  2. call move= and move temp T(std::forward<Args>(args)...) to m_data[m_size]
      //  3. destroy temp T(std::forward<Args>(args)...)
        m_data[m_size] = T(std::forward<Args>(args)...);
#endif
        return m_data[m_size++];
    }

    void popBack()
    {
        if (m_size > 0)
        {
            m_size--;
            m_data[m_size].~T();
        }
    }

    void clear()
    {
        for (size_t i = 0; i < m_size; i++)
        {
            m_data[i].~T();
        }
        m_size = 0;
    }

    const T &operator[](size_t index) const
    {
        if (index >= m_size)
        {
            // assert
        }
        return m_data[index];
    }

    T &operator[](size_t index)
    {
        if (index >= m_size)
        {
            // assert
        }
        return m_data[index];
    }

    size_t size() const { return m_size; }

    size_t capacity() const { return m_capacity; }

    // for (const auto &v : vector) in order to use this we need to implement begin() and end() functions
    Iterator begin()
    {
        return Iterator(m_data);
    }

    Iterator end()
    {
        return Iterator(m_data + m_size);
    }

private:
    void reAllocate(size_t newCapacity)
    {
        if (newCapacity < m_size)
            m_size = newCapacity;

        // allocate memory, do not call (default) constructors
        T *newBlock = (T *)::operator new(newCapacity * sizeof(T));
        for (size_t i = 0; i < m_size; i++)
        {
#if 1 // FIX:
      // 1. move constructor T(T&&) - create object in place (mem = &newBlock[i])
            new (&newBlock[i]) T(std::move(m_data[i]));
#else // ERROR:
      // if T = std::string (nonprimitive type):
      // 1. move= m_data to newBlock[i]
      // 2. because it is assignment (=) operator (not constructor) it tries to Tidy_deallocate() newBlock[i], because newBlock[i]'s data needs to be deleted, BUT there is no object here (only allocated memory)
            newBlock[i] = std::move(m_data[i]);
#endif
        }

        // we dont use clear() function here, because we do not want to make m_size = 0
        for (size_t i = 0; i < m_size; i++)
        {
            m_data[i].~T();
        }
        // deallocate memory, do not call destructors
        ::operator delete(m_data, m_capacity * sizeof(T));

        m_data = newBlock;
        m_capacity = newCapacity;
    }

private:
    T *m_data = nullptr;
    size_t m_size = 0;
    size_t m_capacity = 0;
};