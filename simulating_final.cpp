// Simulating final in C++03

#include <iostream>
using namespace std;

// virtual base class
class MakeFinal {
private:
  MakeFinal() { std::cout << "MakeFinal::MakeFinal()" << std::endl; }
  friend class Final;
};

// final class
class Final : virtual MakeFinal {
public:
  Final() { std::cout << "Final::Final()" << std::endl; }
};

// the constructor of MakeFinal is directly invoked
// by the last class in the hierarchy
// (due to virtual inheritance from MakeFinal)
// but it is not accessible
class Derived : public Final {
public:
  Derived() { std::cout << "Derived::Derived()" << std::endl; }
};

int main() { Derived obj; }
