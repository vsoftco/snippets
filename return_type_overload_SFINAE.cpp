// Overloading on return type via SFINAE

#include <iostream>
#include <type_traits>

template <class T>
int f(T x,
      typename std::enable_if<std::is_same<T, int>::value>::type* = nullptr) {
    std::cout << "int\n";
    return x;
}

template <class T>
double
f(T x,
  typename std::enable_if<std::is_same<T, double>::value>::type* = nullptr) {
    std::cout << "double\n";
    return x;
}

int main() {
    std::cout << f(10) << '\n';
    std::cout << f(42.) << '\n';
}
