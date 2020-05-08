// Expanding a call to variadic template base classes functions
// Question (dvicino): http://stackoverflow.com/q/30563254/3093378
// Answer (T.C.): http://stackoverflow.com/a/30563282/3093378

#include <iostream>

struct A {
    void id() { std::cout << "A "; }
};

struct B {
    void id() { std::cout << "B "; }
};

template <class... As>
struct Expander : public As... {
    void id() {
        using expander = int[];
        (void) expander{0, ((void) As::id(), 0)...};
    }
};

int main() {
    Expander<A, B> expander;
    expander.id();
}
