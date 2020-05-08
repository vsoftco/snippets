// Variadic print, take 2

#include <iostream>

void print() { std::cout << std::endl; }

template <typename Head, typename... Args>
void print(const Head &head, const Args &... args) {
  std::cout << head << " ";
  print(args...);
}

int main() { print("This", 2, 'x', "is a test"); }
