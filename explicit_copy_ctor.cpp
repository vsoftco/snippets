// Explicit copy ctor

#include <iostream>

class Foo
{
public:
    Foo() = default;
    explicit Foo(const Foo&) = default;    
};

int main()
{
    Foo foo1((Foo())); // direct initialization
    Foo foo2 = Foo(); // copy initialization, does not compile
}
