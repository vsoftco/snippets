// Timing in C++14 with auto lambda parameters

#include <iostream>
#include <chrono>

// need C++14 for auto lambda parameters
auto timing = [](auto && F, auto && ... params)
{
    auto start = std::chrono::steady_clock::now();
    //std::forward<decltype(F)>(F) // why apply also on F instead of
    // the line below?
    F(std::forward<decltype(params)>(params)...); // execute the function
    return std::chrono::duration_cast<std::chrono::milliseconds>(
               std::chrono::steady_clock::now() - start).count();
};

void f(std::size_t numsteps) // we'll measure how long this function runs
{
    // need volatile, otherwise the compiler optimizes the loop
    for (volatile std::size_t i = 0; i < numsteps; ++i);
}

int main()
{
    auto taken = timing(f, 500'000'000); // measure the time taken to run f()
    std::cout << "Took " << taken << " milliseconds" << std::endl;

    taken = timing(f, 100'000'000); // measure again
    std::cout << "Took " << taken << " milliseconds" << std::endl;

    std::cout << "Took " << timing(
                  [numsteps = (std::size_t)100000000]
    {
        for (volatile std::size_t i = 0; i < numsteps; ++i);
    }
              ) << " milliseconds" << std::endl;
}