// Two-phase lookup

#include <iostream>

namespace A
{
class MyInt
{
public:
    MyInt(int) {}
};

MyInt operator - (MyInt const&) {return MyInt{0};}
bool operator > (MyInt const&, MyInt const&) {return false;}

// replacing MyInt with int won't work, 
// as int does not have an associated namespace to use in ADL
typedef MyInt Int;
}

template<typename T>
void f(T i)
{
    if (i > 0)
    {
        // found by ADL in POI second lookup phase, no need for forward declaration
        g(-i); 
    }
}

int main()
{
    A::MyInt m(42);
    f(m);
}

namespace A
{
void g(Int)
{
    f<Int>(42); // Point of instantiation (POI)
}
}