// Disabling ADL
// See comment by 0x499602D2 on http://stackoverflow.com/a/30265205/3093378

#include <iostream>

namespace ADL
{
struct Foo {};
void f(const Foo&)
{
    std::cout << "ADL::f" << std::endl;
}
}

int main()
{
    Foo foo{};
    f(ADL::Foo{}); // f found by ADL, compiles
    
    // below (f) is not a function call expression
    // ADL does not kick in, and therefore it does not compile
    (f)(ADL::Foo{}); 
}
