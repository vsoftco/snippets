// Template backdoor: getting access to private members
// via template specialization of a template member function

#include <iostream>

class Foo {
    int x{42};

  public:
    template <typename T>
    void f(T t) {
        std::cout << t << std::endl;
    }
    void display() { std::cout << x << std::endl; }
};

struct my_tag {};

template <> // specialize it
void Foo::f<my_tag>(my_tag) {
    // change a private member variable
    x = 24;
}

int main() {
    Foo foo;
    // std::cout << foo.x; // cannot do that due to private
    foo.display();

    foo.f<my_tag>(my_tag{}); // oops, we access x
    foo.display();
}
