// Fun with templates, showing that a specialization
// can have more parameters than the primary template

#include <iostream>

// partial template
template<typename T>
struct Foo {
    Foo() {std::cout << "Foo<T>\n";}
};

// partial specialization with more arguments than primary template
template<typename R, typename... Params>
struct Foo<R(Params...)>
{
    Foo() {std::cout << "Foo<R(Params...)>\n";}
};

int main()
{
    int x;
    void func();
    Foo<decltype(func)>();
    Foo<decltype(x)>();
}
