// You CAN call private virtual functions via public base interface

#include <iostream>

class Foo
{
public:
    virtual void f()
    {
        std::cout << "Foo::f()" << std::endl;
    }
    virtual ~Foo() = default;
};

class Bar: public Foo
{
private:
    virtual void f() override
    {
        std::cout << "Bar::f()" << std::endl;
    }
};
int main()
{
    Foo *foo = new Bar;
    foo->f();
}
