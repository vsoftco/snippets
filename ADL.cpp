// Argument-dependent name lookup (ADL) or Koenig lookup
#include <algorithm>
#include <iostream>

// some namespace, no need actually, can use the global one
namespace ADL
{
class Foo
{
};

void swap(Foo& lhs, Foo& rhs)
{
    std::cout << "calling Foo::swap" << std::endl;
}
} /* namespace ADL */

template<typename T>
void invoke_swap(T& x)
{
    T y;

    using std::swap; // bring ADL into play
    swap(x, y); // looks first into the namespace x and y belong
    // for a swap defined there that is a better match
    // then the generic std::swap<>
}

int main()
{
    ADL::Foo a;
    int i;

    invoke_swap(a); // calling ADL::Foo::swap via ADL
    invoke_swap(i); // calling std::swap
}
