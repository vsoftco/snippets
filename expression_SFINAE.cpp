// Expression SFINAE

#include <iostream>

struct X {};
struct Y {
    Y(X) {} // converting constructor
};

template <class T> auto f(T t1, T t2) -> decltype(t1 + t2) // #1
{
    std::cout << __PRETTY_FUNCTION__ << std::endl;
    return {};
}
X f(Y, Y) // #2
{
    std::cout << __PRETTY_FUNCTION__ << std::endl;
    return {};
}

int main()
{
    X x1, x2;
    f(x1, x2);  // deduction fails on #1 (cannot add X + X), calls #2
}
