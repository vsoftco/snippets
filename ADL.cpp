// Argument-dependent name lookup (ADL) or Koenig lookup

#include <iostream>
#include <utility>

namespace ADL
{
class Foo {};
void swap(Foo&, Foo&)
{
    std::cout << "calling Foo::swap" << std::endl;
}
} /* namespace ADL */

int main()
{
    ADL::Foo a, b;
    int x = 0, y = 0;
    
    using std::swap; // fall back on std::swap if no better alternatives
    swap(a, b); // finds ADL::swap via ADL, better candidate than std::swap
    swap(x, y); // invokes global swap
}
