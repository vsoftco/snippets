// Storing pointer to functions as template members

#include <iostream>

template <typename T>
class PtrFun {
    T _ptr; // regular pointer to function
  public:
    PtrFun(T ptr) : _ptr(ptr) {}

    template <typename... Args>
    void run(Args&&... args) // run it
    {
        _ptr(std::forward<Args>(args)...);
    }
};

template <typename T>
auto make_PtrFun(T param) {
    return PtrFun<T>(param);
}

void f(int) { std::cout << "void f(int)" << std::endl; }

int main() {
    auto ptr_foo = make_PtrFun(f);
    ptr_foo.run(42);
}
