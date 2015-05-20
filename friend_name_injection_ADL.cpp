// Friend name injection and ADL

#include <iostream>

struct Foo
{
    friend void f(const Foo&) {}
    friend void g() {}
};

int main()
{
    f(Foo{}); // call succeeds due to ADL

    // line below does not compile, even if the name is "injected"
    // into the global namespace; it remains "hidden" for the purpose
    // of name lookup
    // g();
    // ::g(); // same
    // Foo::g(); // g is not a member of Foo
}
