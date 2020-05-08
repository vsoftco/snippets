// std::integer_sequence<> (only in C++14)

#include <iostream>
#include <utility>

struct Foo {
  static int x;
};

int Foo::x = 10;

int main() {
  using Type1 = std::integer_sequence<int, 2, 3, 4>;
  using Type2 = std::make_integer_sequence<int, 5>;

  Type1 i1;
  Type2 i2;

  std::cout << Type1::size() << " " << Type2::size() << std::endl;
  std::cout << i1.size() << " " << i2.size() << std::endl;
}
