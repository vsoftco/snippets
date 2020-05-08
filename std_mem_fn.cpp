// Understanding pointer to members and std::mem_fn

#include <functional>
#include <iostream>

class MyClass {
public:
  MyClass() {
    auto func1 = std::mem_fn(&MyClass::MyFunction);
    func1(this, 42); // call it on the current instance

    auto func2 = &MyClass::MyFunction;
    (this->*func2)(43); // call it on the current instance
  }
  void MyFunction(int i) { std::cout << i << std::endl; }
};

int main() { MyClass foo; }
