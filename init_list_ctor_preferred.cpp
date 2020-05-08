// initializer_list<> constructors trump any other constructors
// http://stackoverflow.com/q/27144054/3093378 (my question)
// http://stackoverflow.com/a/27144307/3093378 (accepted answer)

#include <initializer_list>
#include <iostream>

class Foo {
public:
  Foo(std::initializer_list<Foo>) {
    std::cout << "initializer_list ctor" << std::endl;
  }
  // uncomment explicit to prevent the implicit conversion
  /* explicit */ Foo(int) { std::cout << "ctor" << std::endl; };
  Foo(const Foo &) { std::cout << "copy ctor" << std::endl; }
};

int main(int argc, char const *argv[]) {
  // why is the initializer_list ctor invoked?
  // because initializer_list ctor "trumps" everything!
  Foo foo{10}; // converts 10 to Foo, then uses the init-list ctor
}