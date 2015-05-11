// Factory method for classes having constructors
// that take an arbitary number of parameters

#include <iostream>
#include <memory>

template <typename T, typename... Params>
class Factory
{
public:
    static std::unique_ptr<T> create(Params... params)
    {
        return std::make_unique<T>(params...);
    }
};

struct Foo
{
    Foo(int) {};
};

struct Bar
{
    Bar(bool, double) {};
};

int main()
{
    std::shared_ptr<Foo> foo = Factory<Foo, int>::create(42);
    std::shared_ptr<Bar> bar = Factory<Bar, bool, double>::create(true, 42.5);
}
