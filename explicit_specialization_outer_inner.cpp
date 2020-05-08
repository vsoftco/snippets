// Explicit specialization of member function templates
// of class templates

#include <iostream>

template <typename T>
struct Foo {
    template <typename U>
    void test() {
        std::cout << "[T, U] generic\n";
    }
};

template <>
template <>
void Foo<int>::test<double>() {
    std::cout << "[T = int, U = double] specialization\n";
}

int main() {
    Foo<int> foo;
    Foo<float> bar;

    foo.test<double>();
    bar.test<float>();
}