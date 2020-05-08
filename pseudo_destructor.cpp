// Pseudo-destructor example
// See http://en.cppreference.com/w/cpp/language/destructor
// or
// http://cprogrammers.blogspot.ca/2005/11/c-programming-pseudo-destructors.html

#include <iostream>

using Foo = int; // we need a type alias

int main() {
  int x = 10;
  x.~Foo(); // this is a call to a pseudo-destructor, it is a no-op
  x = 20;
  std::cout << x << std::endl;
}
