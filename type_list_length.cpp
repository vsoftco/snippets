// Type trait that computes the length of a type list
// Essentially an implementation of sizeof... operator

#include <cstddef>
#include <iostream>

template <typename Head, typename... Args> struct lenght_type_list {
  const static std::size_t value = 1 + lenght_type_list<Args...>::value;
};

template <typename Head> struct lenght_type_list<Head> {
  const static std::size_t value = 1;
};

int main() {
  std::cout << lenght_type_list<int, double, float>::value; // prints 3
}
