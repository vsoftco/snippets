// Argument-dependent name lookup (ADL) or Koenig lookup
#include <algorithm>
#include <iostream>

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
    
    using std::swap; // bring ADL into play
    swap(a, b); // finds ADL::swap
    swap(x, y); // invokes global swap
}
