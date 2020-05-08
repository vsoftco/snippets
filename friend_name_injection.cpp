// Friend name injection, a.k.a. Barton–Nackman trick

#include <iostream>

struct X {
  // both of these functions are injected into the global namespace
  // however only f(const X&) is found via ADL
  friend void f(const X &) { std::cout << __PRETTY_FUNCTION__ << std::endl; }
  friend void f() { std::cout << __PRETTY_FUNCTION__ << std::endl; }
};

int main() {
  f(X{}); // OK, in global namespace via ADL

  // f(); // doesn't compile, function is not found via regular name look-up
  // X::f(); // same
  // ::f(); // same
}
