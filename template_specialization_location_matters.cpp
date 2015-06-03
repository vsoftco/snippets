// The place of definition of template explicit specialization matters!
// The Dimov/Abrahams Example
// http://www.gotw.ca/publications/mill17.htm

#include <iostream>

template<class T> // (a) a base template
void f( T )
{
    std::cout << "void f(T)\n";
}

template<class T> // (b) a second base template, overloads (a)
void f( T* )      //     (function templates can't be partially
                  //     specialized; they overload instead)
{
    std::cout << "void f(T*)\n";
}

template<>        // (c) explicit specialization of (b)
void f<>(int*)
{
    std::cout << "void f<>(int*)\n";
}

int main()
{
    int* p = nullptr;
    f(p);           // calls (c); 
    // Note: switching the order of (b) with (c) will result in calling 
    // f(T*), since f<>(int*) will be seen as an explicit specialization of (a)
}