// Enforce N parameters of the same type (double) on a variadic template
// Question: http://stackoverflow.com/q/30179181/3093378
// Answer: http://stackoverflow.com/a/30179412/3093378

#include <cstddef>
#include <iostream>

constexpr std::size_t N = 3;

template<typename, typename...>
struct are_same;

template<typename T, typename Arg>
struct are_same<T, Arg> : std::is_same<T, Arg>
{};

template<typename T, typename Arg, typename... Args>
struct are_same<T, Arg, Args...> :
std::integral_constant < bool, (std::is_same<T, Arg>::value && are_same<T, Args...>::value) >
{};

template <typename... Args>
typename std::enable_if < (are_same<double, Args...>::value && sizeof...(Args) == N), void >::type
/* void */ f(Args... args)
{
    // Do interesting stuff
}

int main()
{
    f(1.1, 2.2, 3.3); // OK, N = 3 doubles
    // f(1.1, 2.2); // doesn't compile, N != 3
    // f(1, 2, 3); // doesn't compile, type deduced as int
}
