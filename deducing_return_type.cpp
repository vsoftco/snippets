// Deducing the return type of a function
// My question and my solution: http://stackoverflow.com/q/30316244/3093378

#include <iostream>
#include <typeinfo>

double f(int); // we deduce the returning type of this function

template<typename Ret, typename... Args>
struct Helper
{
    using type = Ret;
};

template<typename Ret, typename... Args>
Helper<Ret, Args...> invoke(Ret(*fp)(Args...))
{
    return Helper<Ret, Args...> {};
}

template<typename Ret, typename... Args>
using Return_Type = typename Helper<Ret, Args...>::type;

int main()
{
    using return_type = decltype(invoke(f))::type;
    std::cout << typeid(return_type).name() << std::endl; // fine
}