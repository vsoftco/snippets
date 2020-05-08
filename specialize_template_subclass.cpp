// Specializing template subclass
// See http://stackoverflow.com/q/29550788/3093378

#include <iostream>

class Foo {
  public:
    template <typename... Ts>
    struct Bla;
};

template <>
struct Foo::Bla<int> {
    static constexpr int x = 10;
};

int main() { std::cout << Foo::Bla<int>::x << std::endl; }