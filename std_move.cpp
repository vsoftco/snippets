// Understanding std::move
// Compile with -fno-elide-constructors

#include <iostream>
#include <memory>

struct Foo
{
    Foo()
    {
        std::cout << "ctor\n";
    }
    Foo(const Foo&)
    {
        std::cout << "copy\n";
    }
    Foo(Foo&&)
    {
        std::cout << "move\n";
    }
};

struct Factory
{
    static Foo make()
    {
        auto up = Foo();
        std::cout << "just before return in Factory::make\n";
        return up;
    }
};

int main()
{
    auto x = Factory::make();
}
