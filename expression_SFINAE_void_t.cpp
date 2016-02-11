// Expression SFINAE via void_t
// checks wether a class has a specific member function

#include <iostream>
#include <type_traits>

struct Foo
{
    void ham() const;
    void ham();
};

struct Bar {
    void ham() {}
};

template<typename...>
using void_t = int;

template<typename C, typename = int>
struct has_const_ham: std::false_type{};

template<typename C>
struct has_const_ham<C, void_t<decltype(std::declval<const C&>().ham())>> : 
    std::true_type{};

int main()
{
    std::cout << std::boolalpha;
    std::cout << has_const_ham<Foo>::value << std::endl;
    std::cout << has_const_ham<Bar>::value << std::endl;
}