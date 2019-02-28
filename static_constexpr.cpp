// static constexpr initialization example
// Will not work with only static char str[] = "test";

#include <iostream>

struct Foo
{
    // Foo(): str{"won't compile"}{} // will not compile
    static constexpr char str[] = "test";
};
constexpr char Foo::str[];

int main()
{
    std::cout << Foo::str << '\n';
}
