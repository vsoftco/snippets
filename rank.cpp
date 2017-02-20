// Computes the rank (number of dimensions) of a multi-dimensional array 
// at compile time

#include <iostream>
#include <cstddef>

template<typename T>
struct rank
{
    static constexpr std::size_t value = 0;
};

template<typename T>
struct rank<T[]>
{
    static constexpr std::size_t value = 1 + rank<T>::value;
};

template<typename T, std::size_t N>
struct rank<T[N]>
{
    static constexpr std::size_t value = 1 + rank<T>::value;
};

int main()
{
    std::cout << rank<int[][5][7][9]>::value << std::endl;
}
