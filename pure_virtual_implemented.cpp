// Pure virtual functions can be implemented!

#include <iostream>
#include <memory>

struct Base {
  virtual void f() = 0;
  // we MUST implement a pure virtual destructor,
  // since it is automatically invoked by the compiler
  // whenever a derived destructor is invoked
  virtual ~Base() = 0;
};

void Base::f() { std::cout << "Base::f()" << std::endl; }

Base::~Base() { std::cout << "Base::~Base()" << std::endl; }

struct Derived : Base {
  void f() override {
    Base::f(); // default behaviour
    std::cout << "Derived::f()" << std::endl;
  }
};

int main() {
  auto upBase = std::make_unique<Derived>();
  upBase->f();
}
