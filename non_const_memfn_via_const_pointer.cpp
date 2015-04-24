// Invoking non-const member functions of const objects via const pointers
// Undefined behaviour

#include <iostream>

struct Foo
{
    int x{10};
    void f() const
    {
        std::cout << "Foo::f() const" << std::endl;
    }
    void f()
    {
        std::cout << "Foo::f()" << std::endl;
        ++x;
    }
    Foo* pFoo{this};
};

int main(void)
{
    const Foo foo;

    std::cout << foo.x << std::endl; // initially x = 10
    static_cast<const Foo*>(foo.pFoo)->f(); // calls Foo::f() const
    foo.pFoo->f(); // calls Foo::() (non-const)
    std::cout << foo.x << std::endl; // modified x, now x = 11
}