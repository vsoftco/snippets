// You CAN call private virtual functions via public base interface

#include <iostream>

class Base {
public:
  virtual void f() { std::cout << "Base::f()" << std::endl; }
  virtual ~Base() = default;
};

class Derived : public Base {
private:
  virtual void f() override { std::cout << "Derived::f()" << std::endl; }
};
int main() {
  Base *base = new Derived;
  base->f();
}
