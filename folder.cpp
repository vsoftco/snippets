// Left-folder functor that recurses on itself
// See http://stackoverflow.com/a/43787883/3093378 (my SO answer)

#include <iostream>

template <typename T>
class Sum {
    T x_{};

  public:
    Sum& operator()(T x) {
        x_ += x;
        return *this;
    }
    operator T() const { return x_; }
};

int main() {
    Sum<int> s;
    std::cout << s(1)(2)(3)(4)(-5);
}
