// Initializer lists are always preferred, tricky with delegating constructors
// http://stackoverflow.com/q/29763339/3093378
// http://stackoverflow.com/a/29763864/3093378 (my accepted answer)

#include <initializer_list>

struct test
{
    /*explicit*/ test(int) {} // uncomment explicit and no more errors

    // error, implicitly converts 42 to test(42) via the test(int)
    test( std::initializer_list<test> v)
        : test{42} {} 
};

int main() {}
