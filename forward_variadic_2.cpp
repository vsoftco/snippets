// Understanding std::forward and variadic templates, part 2

#include <iostream>

template<typename T>
void f(T&& head)
{
    std::cout << head << " ";
}

template<typename T, typename... Params>
void f(T&& head, Params&&... tail)
{
    std::cout << head << " ";
    f(tail...);
}

template<typename... Params>
void g(Params... params)
{
    f(std::forward<Params>(2 + params)...);
}

int main()
{
    g(2, 3, 4);
}
