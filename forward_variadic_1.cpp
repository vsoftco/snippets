// Understanding std::forward and variadic templates, part 1

#include <iostream>

template <typename... Args> // Types and parameters
void f(Args... args) {
  std::cout << sizeof...(Args) << " parameters \n";
  std::cout << "f(Args... args)\n";
}

template <typename... Args> // Only types
void g() {
  std::cout << sizeof...(Args) << " types \n";
  std::cout << "g<Args...>()\n";
}

template <typename... Args> void forward_to_f(Args &&... args) {
  std::cout << "Forwarding to f...\n";
  f(std::forward<Args>(args)...);
}

template <typename... Args> void forward_to_g() {
  std::cout << "Forwarding to g...\n";
  g<Args...>();
}

int main() {
  forward_to_f(1, 2, 5);
  forward_to_g<int, double>();
}
