// A basic implementation of std::mem_fn

#include <functional>
#include <iostream>
#include <memory>

struct Foo
{
    int _m;
    Foo(int m): _m(m) {}

    int get() const
    {
        std::cout << "void Foo::get() const" << std::endl;
        return _m;
    }

    void add(int m)
    {
        std::cout << "int Foo::add()" << std::endl;
        _m += m;
    }
};

template<class R, class T>
class Wrapper
{
    R T::*_ptr; // pointer to member function
public:
    Wrapper(R T::*ptr): _ptr(ptr) {}

    template<typename... Args>
    void operator()(T& obj, Args&&... args) const
    {
        (obj.*_ptr)(std::forward<Args>(args)...);
    }

    template<typename... Args>
    void operator()(const T& obj, Args&&... args) const
    {
        (obj.*_ptr)(std::forward<Args>(args)...);
    }

    template<typename... Args>
    void operator()(T* obj, Args&&... args) const
    {
        (obj->*_ptr)(std::forward<Args>(args)...);
    }

    template<typename... Args>
    void operator()(const T* obj, Args&&... args) const
    {
        (obj->*_ptr)(std::forward<Args>(args)...);
    }
};

template< class R, class T >
auto my_mem_fn(R T::* pm)
{
    return Wrapper<R, T> {pm};
}

int main()
{
    Foo foo(42);
    const Foo cfoo(42);

    Foo* pFoo = new Foo(42);
    const Foo* cpFoo = new Foo(42);

    auto memfn1 = my_mem_fn(&Foo::get);
    auto memfn2 = my_mem_fn(&Foo::add);

    memfn1(foo);
    memfn1(cfoo);
    memfn1(pFoo);
    memfn1(cpFoo);

    memfn2(foo, 10);
    memfn2(pFoo, 10);
    // memfn2(cfoo, 10);  // const violation
    // memfn2(cpFoo, 10); // const violation

    delete pFoo;
    delete cpFoo;
}
