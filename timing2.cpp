// Timing in C++14

#include <iostream>
#include <chrono>
#include <functional>

// we will time this function
void f(std::size_t numsteps)
{
    for (volatile std::size_t i = 0; i < numsteps; ++i);
}

struct X {
    // we will time this member function
    void f(std::size_t numsteps)
    {
        for (volatile std::size_t i = 0; i < numsteps; ++i);
    }
};

// time regular functions
template<class Fun, class... Params>
auto timing(Fun&& F, Params&& ... params)
{
    auto start = std::chrono::steady_clock::now();
    std::forward<decltype(F)>(F)
    (std::forward<decltype(params)>(params)...); // execute the function
    return std::chrono::duration_cast<std::chrono::milliseconds>(
               std::chrono::steady_clock::now() - start).count();
};

// time member functions
template<class Return, class Object, class... Params1, class... Params2>
auto timing(Return (Object::*fp)(Params1...), Params2... params)
{
    auto start = std::chrono::steady_clock::now();
    (Object{}.*fp)(std::forward<decltype(params)>(params)...);
    return std::chrono::duration_cast<std::chrono::milliseconds>(
               std::chrono::steady_clock::now() - start).count();
};

int main()
{
    auto taken1 = timing(f, 500'000'000); // measure the time taken to run f()
    std::cout << "Took " << taken1 << " milliseconds" << std::endl;

    auto taken2 = timing(&X::f, 500'000'000); // measure the time taken to run X::f()
    std::cout << "Took " << taken2 << " milliseconds" << std::endl;
}
