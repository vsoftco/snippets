// constexpr example

#include <type_traits>
#include <iostream>

template<class T>
void f(T x) {
    // if (std::is_floating_point<T>::value) won't compile, as both branches
    // should compile
    if constexpr (std::is_floating_point<T>::value) {
        std::cout << std::abs(x) << '\n';
    }
    // this branch is discarded at compile time
    // should be valid for at least one specialization
    else {
        std::cout << x << '\n';
    }
}

// Outside a template, a discarded statement is fully checked. if constexpr is
// not a substitute for the #if preprocessing directive; won't compile as is
/*
void g() {
     if constexpr(false) {
        int i = 0;
        int *p = i; // Error even though in discarded statement
    }
}
*/

int main() {
    f(-2.6);
    f("test");
}
