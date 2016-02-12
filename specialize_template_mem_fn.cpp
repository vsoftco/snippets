// Specializing template member functions of class templates

#include <iostream>

template<typename T>
struct Foo
{
    template<typename U>
    void f();
};

/* OK, generic definition */
template<typename T> // outer
    template<typename U> // inner
void Foo<T>::f()
{
    std::cout << "Generic: " << __PRETTY_FUNCTION__ << std::endl;
}

/* OK, everything is fully specialized */
template<> // outer
    template<> // inner
void Foo<int>::f<int>()
{
    std::cout << "Specialization: " << __PRETTY_FUNCTION__ << std::endl;
}

/* NOT ALLOWED, seen as partial specialization of mem fn F<>
template<typename T> // outer
    template<typename U> // inner
void Foo<T>::f<U>(){}
*/ 

/* NOT ALLOWED, partial specialization
template<>
    template<typename U>
void Foo<int>::f<U>(){}
*/

/* NOT ALLOWED, enclosing class must be fully specialized
template<typename T>
    template<>
void Foo<T>::f<double>(){}
*/ 

int main()
{
    Foo<int> foo_int;
    Foo<double> foo_double;

    foo_int.f<int>();
    foo_int.f<double>();

    foo_double.f<int>();
    foo_double.f<double>();
}
