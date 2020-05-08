// GMP-style argument passing

#include <iostream>

struct Foo {
  int x;
  double y;
};
using Foo_t = Foo[1];

void f(Foo_t foo) // pass by "reference"
{
  foo->x = 42;
  foo->y = 42.42;
}

int main() {
  Foo_t foo{1, 2};
  std::cout << foo->x << " " << foo->y << std::endl;
  f(foo); // we modify foo
  std::cout << foo->x << " " << foo->y << std::endl;
}
