// Explicit copy constructor

#include <iostream>

class Foo {
public:
  Foo() = default;
  explicit Foo(const Foo &) = default;
};

Foo foo() {
  Foo foo;
  return foo; // oops, cannot copy into the return value
}

int main() {
  Foo foo1((Foo())); // direct initialization
  Foo foo2 = Foo();  // copy initialization, does not compile
}
