// Understanding std::ref

#include <functional>
#include <iostream>

// some function that takes a parameter by reference
template <typename T>
void inc(T& x) // increment x
{
    ++x;
}

// a by-value template function that invokes inc()
template <typename T>
void f(T x) // by-value, reference and cv qualifiers are discarded
{
    inc(x);
}

int main() {
    int x{10};
    std::cout << "Initial x: " << x << std::endl;
    inc(x); // increment x
    std::cout << "After inc(x): " << x << std::endl;
    f(x); // we won't modify x, as ref and cv qualifiers are stripped
    std::cout << "After f(x): " << x << std::endl;
    f(std::ref(x)); // now we DO MODIFY x
    std::cout << "After f(std::ref(x)): " << x << std::endl;
}
