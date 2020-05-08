// Pointer to member function

#include <iostream>

struct Foo {
    void say() { std::cout << "Say something!" << std::endl; }
};

using ptr_mem_fn = auto (Foo::*)() -> void;
// same as
// typedef void (Foo::*ptr_mem_fn)();

int main() {
    Foo foo;
    ptr_mem_fn fpFoo = &Foo::say;
    (foo.*fpFoo)();
}