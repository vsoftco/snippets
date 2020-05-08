// Inner classes need a reference to the current instance

#include <iostream>

class Foo {
    int _n;

  public:
    class Inner {
        Foo& rFoo; // stores the reference to outer class instance
      public:
        Inner(Foo& foo) : rFoo(foo) {}
        int getx() {
            // OK, in C++11 inner classes have access, no need for friend
            return rFoo._n;
        }
    } inner;

    Foo(int n) : _n(n), inner(*this) {}
};
int main() {
    Foo foo(42);
    std::cout << foo.inner.getx() << std::endl;
}
