// Default template parameters injection into specializations

#include <iostream>

template<typename T>
struct Comp
{
    Comp() {std::cout << "Comp<T>\n";}
};

template<>
struct Comp<int>
{
public:
    Comp() {std::cout << "Comp<int>\n";}
};

// default template parameter
template<typename T, typename C = Comp<T>>
struct X
{
    C c{};
};

// default template parameters are kept in specializations
// cannot re-define them explicitly
template<typename C>
struct X<int, C>
{
    C c{};
};

int main()
{
    X<double> x;
    X<int> y;
}
