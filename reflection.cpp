// Basic compile-time reflection in C++11

#include <cstddef>
#include <iostream>
#include <typeinfo>

template<typename R, typename... Args>
struct Inspect;

template<typename R, typename... Args>
struct Inspect<R(Args... args)>
{
    using ReturnT = R; // return type
    const static std::size_t ParamN = sizeof...(Args); // number of parameters
};

double f(int, float);

int main()
{
    std::cout << typeid(Inspect<decltype(f)>::ReturnT).name() << std::endl;
    std::cout << Inspect<decltype(f)>::ParamN << std::endl;
}
