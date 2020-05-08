// Template default parameters are ignored in template type matching

template <typename...> class void_t {}; // type list

template <typename, typename = void> class Foo {};

template <template <typename T, typename = void_t<T>> class>
void f() {} // accepts only template <typename, typename>

template <template <typename T> class>
void g() {} // accepts only template <typename>

template <typename T> // template alias, ignore the second template parameter
using Foo_single = Foo<T>;

int main() {
  f<Foo>();
  // g<Foo>();     // error, default template parameters of Foo are ignored
  g<Foo_single>(); // this works!
}
