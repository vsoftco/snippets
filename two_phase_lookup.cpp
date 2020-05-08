// Two-phase lookup

#include <iostream>

namespace A {
class MyInt {
public:
  MyInt(int) {}
};

MyInt operator-(MyInt const &) { return MyInt{0}; }
bool operator>(MyInt const &, MyInt const &) { return false; }

// replacing MyInt with int won't work,
// as int does not have an associated namespace to use in ADL
typedef MyInt Int;
} // namespace A

template <typename T> void f(T i) {
  if (i > 0) {
    // found by ADL at POI second-phase lookup, no need for forward declaration
    g(-i);
  }
}

int main() {
  A::MyInt m(42);
  f(m);
}

namespace A {
// this is NOT found at second-phase lookup, since only ADL is performed
void g() {}

// found by ADL at POI second-phase lookup, no need for forward declaration
void g(Int) { f<Int>(42); }
// Point of instantiation (POI) is here
} // namespace A