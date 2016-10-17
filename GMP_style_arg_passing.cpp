// GMP-style argument passing

#include <iostream>

struct Foo
{
    int x{};
    double y{};
};
using Foo_t = Foo[1];

void f(Foo_t foo) // pass by "reference"
{
    foo->x = 42;
    foo->y = 42.42;
}

int main()
{
    Foo_t foo1{1, 2};
    std::cout << foo1->x << " " << foo1->y << std::endl;
    f(foo1);
    std::cout << foo1->x << " " << foo1->y << std::endl;
}
