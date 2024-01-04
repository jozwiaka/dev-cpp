#include <iostream>
#include <thread>
#include <string>
#include <future>
#include <vector>
#include <list>
#include <mutex>
#include <memory>
#include <typeindex>
#include <typeinfo>
#define LINE std::cout << "----------------------\n";

namespace STD
{
    // ### IntegralConstant ###
    template <typename Ty, Ty Val>
    struct IntegralConstant
    {
        static constexpr Ty Value = Val;

        using ValueType = Ty;
        using Type = IntegralConstant;

        constexpr operator ValueType() const noexcept
        {
            return Value;
        }

        [[nodiscard]] constexpr ValueType operator()() const noexcept
        {
            return Value;
        }
    };

    template <bool Val>
    using BoolConstant = IntegralConstant<bool, Val>;

    // ### RemoveRef ###
    template <typename Ty>
    struct RemoveRef
    {
        using Type = Ty;
    };

    template <typename Ty>
    struct RemoveRef<Ty &>
    {
        using Type = Ty;
    };

    template <typename Ty>
    struct RemoveRef<Ty &&>
    {
        using Type = Ty;
    };

    template <typename Ty>
    using RemoveRefT = RemoveRef<Ty>::Type;

    // ### IsLvalueReference ###
    template <typename>
    inline constexpr bool IsLvalueReferenceV = false;

    template <typename Ty>
    inline constexpr bool IsLvalueReferenceV<Ty &> = true;

    template <typename Ty>
    struct IsLvalueReference : BoolConstant<IsLvalueReferenceV<Ty>>
    {
    };

    // ### IsRvalueReference ###
    template <typename>
    inline constexpr bool IsRvalueReferenceV = false;

    template <typename Ty>
    inline constexpr bool IsRvalueReferenceV<Ty &&> = true;

    template <typename Ty>
    struct IsRvalueReference : BoolConstant<IsRvalueReferenceV<Ty>>
    {
    };

    template <typename T>
    std::string Type(T &&arg)
    {
    }

    // ### Forward ###

    // T&& &&, it collapses to T&&.
    // T& &&, it collapses to T&.
    // T&& &, it collapses to T&.
    // T& &, it collapses to T&.

    template <typename Ty>
    [[nodiscard]] constexpr Ty &&Forward(RemoveRefT<Ty> &arg) noexcept
    {
        std::cout << "Forward(&) " << typeid(arg).name() << "\n";
        return static_cast<Ty &&>(arg);
    };

    template <typename Ty>
    [[nodiscard]] constexpr Ty &&Forward(RemoveRefT<Ty> &&arg) noexcept
    {
        std::cout << "Forward(&&) " << typeid(arg).name() << "\n";
        static_assert(!IsLvalueReferenceV<Ty>, "Bad forward call");
        return static_cast<Ty &&>(arg);
    };

    // ### Move ###
    template <typename Ty>
    [[nodiscard]] constexpr RemoveRefT<Ty> &&Move(Ty &&arg) noexcept
    {
        return static_cast<RemoveRefT<Ty> &&>(arg);
    };
}

struct Entity
{
    int x, y;
};

void CheckArgType(Entity &arg)
{
    std::cout << "CheckArgType(&)\n";
}

void CheckArgType(Entity &&arg)
{
    std::cout << "CheckArgType(&&)\n";
}

template <typename Ty>
void Test(Ty &&t) // Ty&& = Entity& || Entity&&
{
    CheckArgType(t);
    CheckArgType(STD::Forward<Ty>(t));
    LINE
}

void TestEntity(Entity &e)
{
    using EntityRef = Entity &;
    CheckArgType(e);
    CheckArgType(static_cast<EntityRef &&>(e)); // explicit forward //T& && -> T&
    CheckArgType(STD::Forward<Entity &>(e));
    LINE
}

void TestEntity(Entity &&e)
{
    using EntityRef = Entity &&;
    // e = static_cast<EntityRef &&>(e);           //! Won't change CheckArgType(&) to CheckArgType(&&) in the next line, because it is not being casted in the MOMENT OF CALLING
    CheckArgType(e);                            //! CheckArgType(&) -> in order to call && overload you have to explicitly cast it to && IN MOMENT OF CALLING
    CheckArgType(static_cast<EntityRef &&>(e)); // explicit forward //T&& && -> T&&
    CheckArgType(STD::Forward<Entity &&>(e));
    LINE
}

int main()
{
    std::cout << STD::IsRvalueReferenceV<int> << std::endl;
    std::cout << STD::IsLvalueReferenceV<int &> << std::endl;
    std::cout << STD::IsRvalueReferenceV<int &&> << std::endl;
    LINE;

    Entity e{1, 2};

    STD::Forward<Entity>(e);            // rval
    STD::Forward<Entity>(STD::Move(e)); // lval
    // STD::Forward<Entity>(Entity(1, 2)); // lval
    LINE;

    Test(e);            // rval
    Test(STD::Move(e)); // lval
    // Test(Entity(1, 2)); // lval

    TestEntity(e);
    TestEntity(STD::Move(e));
    // TestEntity(Entity(1, 2));
}
