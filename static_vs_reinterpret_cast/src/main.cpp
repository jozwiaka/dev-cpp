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

void myFunction()
{ /*...*/
}

int main()
{
    int i = 2;
    double d = *reinterpret_cast<double *>(&i); // wrong value
    print(d);
    double d1 = static_cast<double>(i); // 2 - correct
    print(d1);

    // 1. Pointer to Integer
    int *ptr = new int;
    uintptr_t value = reinterpret_cast<uintptr_t>(ptr);
    // int intValue = static_cast<int>(ptr); // Error: cannot cast pointer to integer with static_cast

    // 2. Integer to Pointer
    int intValue = 42;
    int *ptr2 = reinterpret_cast<int *>(intValue);
    // int* ptr2 = static_cast<int*>(intValue);  // Error: cannot cast integer to pointer with static_cast

    // 3. Pointer to Void Pointer
    int *intValue2 = new int;
    void *voidPtr = reinterpret_cast<void *>(intValue2);
    // void* voidPtr = static_cast<void*>(intValue2);  // Error: cannot cast pointer to void pointer with static_cast

    // 4. Reference to Pointer
    int x = 10;
    int &ref = x;
    int *ptr3 = reinterpret_cast<int *>(&ref);
    // int* ptr3 = static_cast<int*>(&ref);  // Error: cannot cast reference to pointer with static_cast

    // 5. Pointer to Function Pointer
    void (*funcPtr)() = reinterpret_cast<void (*)()>(myFunction);
    // void (*funcPtr)() = static_cast<void(*)()>(myFunction);  // Error: cannot cast pointer to function pointer with static_cast

    // 6. Pointer to Unrelated Class
    class A
    {
    };
    class B
    {
    };
    A *aPtr = new A;
    B *bPtr = reinterpret_cast<B *>(aPtr);
    // B* bPtr = static_cast<B*>(aPtr);  // Error: cannot cast pointer to unrelated class with static_cast

    // 7. Pointer to Array
    int *intPtr = new int[5];
    int(*arrPtr)[5] = reinterpret_cast<int(*)[5]>(intPtr);
    // int (*arrPtr)[5] = static_cast<int(*)[5]>(intPtr);  // Error: cannot cast pointer to array with static_cast

    // 9. Pointer to Member Object
    struct MyClass
    {
        int value;
    };
    int MyClass::*memberPtr = &MyClass::value;
    int MyClass::*reinterpretMemberPtr = reinterpret_cast<int MyClass::*>(memberPtr);
    // int MyClass::* staticMemberPtr = static_cast<int MyClass::*>(memberPtr);  // Error: cannot cast pointer to member with static_cast

    // 10. Pointer to Member Function
    struct MyClass2
    {
        void myFunction()
        { /*...*/
        }
    };
    void (MyClass2::*memberFunc)() = &MyClass2::myFunction;
    void (MyClass2::*reinterpretFunc)() = reinterpret_cast<void (MyClass2::*)()>(memberFunc);
    // void (MyClass2::*staticFunc)() = static_cast<void (MyClass2::*)()>(memberFunc);  // Error: cannot cast pointer to member function with static_cast

    // Output for demonstration purposes
    std::cout << "Example code demonstrating reinterpret_cast and static_cast\n";
}
