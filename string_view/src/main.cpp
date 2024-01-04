#include <iostream>
#include <thread>
#include <string>
#include <future>
#include <vector>
#include <list>
#include <mutex>
#include <memory>
#include <string_view>

template <typename T>
void print(T &&t)
{
    std::cout << std::forward<T>(t) << std::endl;
}

// Use string_view over string when there is a read only data
// string_view = a non-owning reference to a string
// useful for providing an abstraction on top of strings e.g. for parsing

class StringView
{
public:
    using ValueType = char;
    using SizeType = std::size_t;

public:
    constexpr StringView() noexcept : m_Data(nullptr), m_Size(0) {}

    constexpr StringView(const ValueType *str) noexcept : m_Data(str), m_Size(str ? std::char_traits<ValueType>::length(str) : 0) {}

    constexpr StringView(const ValueType *str, SizeType count) noexcept : m_Data(str), m_Size(count) {}

    constexpr const ValueType *Data() const noexcept
    {
        return m_Data;
    }

    constexpr SizeType Size() const noexcept
    {
        return m_Size;
    }

    constexpr const ValueType &operator[](SizeType index) const
    {
        return m_Data[index];
    }

private:
    const ValueType *m_Data;
    SizeType m_Size;
};

int main()
{
    StringView mySw{"Text"};
    print(mySw.Data());

    std::string_view sv{"Text"};

    std::wstring_view wsv{L"Text"};

    char array[3] = {'a', 'b', 'c'};
    std::string_view sv_array(array, std::size(array));

    std::string str{"   trim me"};
    std::string_view v{str};
    v.remove_prefix(std::min(v.find_first_not_of(" "), v.size()));
    print(v); //"trim me";

    std::string sEdit = "Text";
    std::string_view svEdit{sEdit};
    svEdit = "Edited"; // probably when I try to modify sv, I sv cretes new data pointer
    print(svEdit);     // Edited
    print(sEdit);      // Text //SHOCKING

    std::string s = "Test Program";
    std::string_view svv(s);

    print(svv);
    s = "ABCD\0";
    print(svv);
}
