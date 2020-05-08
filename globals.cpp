// Simple solution for embedding global variables into your code

#include <iostream>
#include <stdexcept>

// in a header file Globals.h
class Globals {
    static bool ok;
    static int _var1;
    static int _var2;

  public:
    static void init(int var1, int var2) noexcept {
        ok = true;
        _var1 = var1;
        _var2 = var2;
    }
    // getters
    static int var1() noexcept {
        if (!ok)
            throw std::runtime_error("Error: members not initialized");
        return _var1;
    }
    static int var2() noexcept {
        if (!ok)
            throw std::runtime_error("Error: members not initialized");
        return _var2;
    }
};

// in a cpp file Globals.cpp
// those define (allocate storage for) the static memebers
bool Globals::ok = false;
int Globals::_var1, Globals::_var2;

// in the main program, #include "Globals.h"
int main() {
    Globals::init(42, 10);
    std::cout << Globals::var1() << std::endl;
    std::cout << Globals::var2() << std::endl;
}
