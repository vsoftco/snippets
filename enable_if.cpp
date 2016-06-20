#include <iostream>
#include <type_traits>
#include <typeinfo>

template<typename T>
std::enable_if_t<std::is_same<int,T>::value, int>
foo(T x)
{
    std::cout << "Int overload\n";
    return x;
}

template<typename T>
std::enable_if_t<std::is_same<double,T>::value, double>
foo(T x)
{
    std::cout << "Double overload\n";
    return x;
}

int main()
{
    std::cout << foo(42.5) << std::endl;
    std::cout << foo(42) << std::endl;
    // the line below won't compile, substitution error
    // std::cout << foo("test") << std::endl; 
}
