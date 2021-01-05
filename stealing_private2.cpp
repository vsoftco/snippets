// Stealing private members, take 2, simplified with explanations
// See stealing_private1.cpp for a more general solutions
// The code is adapted from http://cpp.kjx.cz/private_backdoor.html
//
// See also:
// https://stackoverflow.com/q/424104/3093378
// https://stackoverflow.com/questions/12993219/access-private-member-using-template-trick
//
// And also Overload 156 (pg. 22)
// https://members.accu.org/index.php/journals/2776

#include <iostream>

class Foo {
  public:
    int getx() const { return _x; }

  private:
    int _x{42};
};

// access rules are not enforced in templates
// so circumvent the access rules by using a pointer-to-member
template <int Foo::*mem_ptr>
struct Thief {
    friend int& steal(Foo& foo) { return foo.*mem_ptr; }
};

// make the Thief friend function visible outside
int& steal(Foo& foo);

// implicit instantiation which in effect defines int& steal(Foo& foo);
template struct Thief<&Foo::_x>;

int main() {
    Foo foo;
    std::cout << foo.getx() << '\n';
    steal(foo) = 100;

    // bam, proof:
    std::cout << foo.getx() << '\n';
}
