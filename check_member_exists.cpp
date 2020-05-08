// Checks whether a class/struct has the member foo
// http://stackoverflow.com/q/29717740/3093378 and the answer
// http://stackoverflow.com/a/29717811/3093378

#include <iostream>
#include <type_traits>

class Foo {
public:
  int foo;
};

class Bar {};

template <typename T> struct has_foo {
  template <typename U> static std::true_type test(decltype(U::foo) *);

  template <typename U> static std::false_type test(...);

  using type = decltype(test<T>(0));
};

template <typename T> using has_foo_t = typename has_foo<T>::type;

int main() {
  std::cout << std::boolalpha
            << std::is_same<has_foo_t<Foo>, std::true_type>::value << std::endl;

  std::cout << std::boolalpha
            << std::is_same<has_foo_t<Bar>, std::true_type>::value << std::endl;
}
