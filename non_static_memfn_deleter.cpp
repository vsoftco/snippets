// std::unique_ptr with non-static member function deleter
// http://stackoverflow.com/q/29525370/3093378

#include <functional>
#include <iostream>
#include <memory>

class Foo {
  private:
    std::unique_ptr<int, std::function<void(int*)>> _up;

  public:
    Foo()
        : _up(new int[42],
              std::bind(&Foo::deleter, this, std::placeholders::_1)) {}
    // With a lambda:
    // Foo(): _up(new int[42],
    //             [=](int* p)->void
    //             {
    //                 deleter(p);
    //             }
    //         ){}
    //
    void deleter(int* p) {
        delete[] p;
        std::cout << "In deleter" << std::endl;
    }
};

int main() { Foo foo; }
