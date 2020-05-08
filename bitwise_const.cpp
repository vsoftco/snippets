// Bitwise const but not logically-const

#include <cstddef>
#include <iostream>

struct Foo {
  int *p;
  Foo() : p(new int[10]) {}
  int &operator[](std::size_t n) const { return p[n]; }
  ~Foo() { delete[] p; }
};

int main() {
  const Foo f;
  f[1] = -1;
  std::cout << f.p[1] << std::endl;
}
