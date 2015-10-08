// Template non-type parameters linkage

template<int N> struct Foo {};
template<const int& N> struct Bar {};

int bar = 42; // must have linkage

int main ()
{
    const int foo = 42; // must be a constant expression, no linkage

    Foo<foo>{}; // OK
    Bar<bar>{}; // OK
}
