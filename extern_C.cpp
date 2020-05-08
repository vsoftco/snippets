// extern "C" inside C++ namespace, see
// https://stackoverflow.com/questions/28996944/extern-c-linkage-inside-c-namespace

#include <iostream>

namespace X {
extern "C" {
void test() { std::cout << "C linkage\n"; }
}

// void test() {} // won't compile!

void test(int) { std::cout << "C++ linkage\n"; }
} // namespace X

// all extern "C" functions share the same space of names
// so we can "bring" test() into the global namespace
extern "C" void test();

int main() {
    X::test();   // C linkage
    test();      // C linkage
    X::test(42); // C++ linkage
}