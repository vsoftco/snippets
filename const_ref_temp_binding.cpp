// Binding a temporary to a const reference
// Direct (works) and indirect (does not work) binding

#include <iostream>

struct Foo
{
    ~Foo()
    {
        std::cout << "\t~Foo" << std::endl;
    }
};

const Foo& f(const Foo& foo)
{
    return foo;
}

int main()
{
    std::cout << "Direct binding to const reference" << std::endl;
    const Foo& foo = Foo{}; // OK, temporary binds to const reference
    
    std::cout << "Attempt of indirect binding" << std::endl;
    const Foo& bar = f(Foo()); // does not bind indirectly 

    std::cout << "Exiting..." << std::endl;
}
