// Enforcing the same class in the CRTP pattern
// Question: http://stackoverflow.com/q/30232004/3093378
// Answer: http://stackoverflow.com/a/30232317/3093378

template<typename T>
class Base
{
    Base() = default;
    friend T; // only T can construct Base
};
class Other {};

class B : public Base<B> {}; // OK

class C : public Base<Other> {}; // won't compile on instantiation

int main()
{
    B b;
    // C c; // won't compile, private constructor
}
