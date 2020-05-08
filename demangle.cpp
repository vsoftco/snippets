// Name demangling with g++
// same as command-line c++filt -n "name"

#include <iostream>
#include <memory>
#include <string>
#include <typeinfo>

#ifdef __GNUG__ // g++
#include <cxxabi.h>
std::string demangle(const char *name) {
  int status;

  // enable c++11 by passing the flag -std=c++11 to g++
  std::unique_ptr<char, void (*)(void *)> res{
      abi::__cxa_demangle(name, NULL, NULL, &status), std::free};

  return (status == 0) ? res.get() : name;
}
#else // not g++
std::string demangle(const char *name) { return name; }
#endif

class Foo {};

int (*p)(Foo *);

int main() {
  std::cout << typeid(p).name() << std::endl;
  std::cout << demangle(typeid(p).name()) << std::endl;
}
