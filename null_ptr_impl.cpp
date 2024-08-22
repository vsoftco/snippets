// A simple implementation of a nullptr-like pointer type

#include <iostream>
#include <memory>

struct null_pointer {
    template <typename T>
    operator T*() {
        std::cout << "Converting to raw pointer" << std::endl;
        return (T*)(0);
    }

    template <typename T>
    operator std::shared_ptr<T>() {
        std::cout << "Converting to std::shared_ptr<>" << std::endl;
        return std::shared_ptr<T>{};
    }

    template <typename T>
    operator std::unique_ptr<T>() {
        std::cout << "Converting to std::unique_ptr<>" << std::endl;
        return std::unique_ptr<T>{}; // invokes the move constructor
    }
};

void f(void*) { std::cout << "void f(void*)" << std::endl; }

void f(int) { std::cout << "void f(int)" << std::endl; }

void g(int) { std::cout << "void g(int)" << std::endl; }

int* h() { return null_pointer{}; }

int main() {
    null_pointer np;

    // Calls, distinguish int vs null_pointer
    f(np); // calls f(void*), via implicit conversion to raw pointer
    f(0);  // calls f(int)
    // g(np); // does not compile

    // Explicit conversions to raw pointers
    (void*)np;
    h();

    // Conversions to smart pointers
    std::shared_ptr<int> spint = np;
    std::unique_ptr<int> upint = np;
}
