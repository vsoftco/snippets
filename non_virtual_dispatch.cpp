// "Virtualization" without virtual, via binding temporaries to
// const references (A. Alexandrescu's trick)

#include <iostream>

using namespace std;

struct A {
    ~A() { cout << "~A" << endl; }
};

struct B : A {
    ~B() { cout << "~B" << endl; }
};

int main() {
    const A& a = B(); // calling the right destructor without virtual dispatch!
}
