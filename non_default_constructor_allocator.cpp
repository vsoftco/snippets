// Allocating memory for non-default constructible objects
// This is how probably std::vector works

#include <iostream>

class Foo
{
    int _m;
public:
    Foo(int m): _m(m){}
    int get_m() const
    {
        return _m;
    }
};

int main()
{
    // allocate memory even if the object is non-default constructible
    Foo* storage = 
        static_cast<Foo*>(
            static_cast<void*>(new char[sizeof(Foo)])
        );
    
    // we can now place our object
    new(storage) Foo(42);

    // display
    std::cout << storage->get_m() << std::endl;
}
