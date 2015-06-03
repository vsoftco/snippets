// Using (almost) const char* as template parameters
// Question I asked: http://stackoverflow.com/q/30604686/3093378

#include <iostream>

template<const char* msg>
void display()
{
    std::cout << msg << std::endl;
}

// Need to have external linkage
// so that there are no multiple definitions
extern const char str1[] = "Test 1";

// Why constexpr is enough? Does it have external linkage?
constexpr char str2[] = "Test 2";

// Why doesn't this work?
extern const char* str3 = "Test 3"; // doesn't work

// Why doesn't this work?
using C_PTR_CHAR = const char* const;
extern constexpr C_PTR_CHAR str4 = "Test 4"; // doesn't work

int main()
{
    display<str1>();
    display<str2>();
    //display<str3>(); // doesn't compile
    //display<str4>(); // doesn't compile
}
