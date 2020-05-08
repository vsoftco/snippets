// Simulating final via CRTP

#include <iostream>

template <typename T>
class MakeFinal {
  private:
    MakeFinal(){};
    friend T;
};

// final class
class Final : virtual MakeFinal<Final> {
  public:
    Final() { std::cout << "Final::Final()" << std::endl; }
};

// the constructor of MakeFinal is directly invoked
// by the last class in the hierarchy (due to virtual MakeFinal)
// but it is not accessible
class Derived : public Final {
  public:
    Derived() { std::cout << "Derived::Derived()" << std::endl; }
};

int main() { Final obj; }
