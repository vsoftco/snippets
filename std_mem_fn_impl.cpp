// A basic implementation of std::mem_fn

#include <functional>
#include <iostream>

struct Foo {
  int _m;
  Foo(int m) : _m(m) {}

  int get() const {
    std::cout << "void Foo::get() const" << std::endl;
    return _m;
  }

  void add(int m) {
    std::cout << "int Foo::add()" << std::endl;
    _m += m;
  }
};

template <typename PTR> class Wrapper {
  PTR _ptr; // pointer to member function
public:
  Wrapper(PTR ptr) : _ptr(ptr) {}

  template <typename T, typename... Args>
  void operator()(T &obj, Args &&... args) const {
    (obj.*_ptr)(std::forward<Args>(args)...);
  }

  template <typename T, typename... Args>
  void operator()(const T &obj, Args &&... args) const {
    (obj.*_ptr)(std::forward<Args>(args)...);
  }

  template <typename T, typename... Args>
  void operator()(T &&obj, Args &&... args) const {
    (obj.*_ptr)(std::forward<Args>(args)...);
  }

  template <typename T, typename... Args>
  void operator()(T *obj, Args &&... args) const {
    (obj->*_ptr)(std::forward<Args>(args)...);
  }

  template <typename T, typename... Args>
  void operator()(const T *obj, Args &&... args) const {
    (obj->*_ptr)(std::forward<Args>(args)...);
  }
};

template <class PTR> auto my_mem_fn(PTR ptr) { return Wrapper<PTR>{ptr}; }

int main() {
  Foo foo(42);
  const Foo cfoo(42);

  Foo *pFoo = new Foo(42);
  const Foo *cpFoo = new Foo(42);

  auto memfn1 = my_mem_fn(&Foo::get);
  auto memfn2 = my_mem_fn(&Foo::add);

  memfn1(foo);
  memfn1(cfoo);
  memfn1(pFoo);
  memfn1(cpFoo);
  memfn1(Foo{42}); // works with rvalues also

  memfn2(foo, 10);
  memfn2(pFoo, 10);
  memfn2(Foo{42}, 10); // works with rvalues also
  // memfn2(cfoo, 10);    // const violation
  // memfn2(cpFoo, 10);   // const violation

  delete pFoo;
  delete cpFoo;
}
