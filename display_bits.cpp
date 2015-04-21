// Display bits at runtime (cannot use std::bitset<> in this case)

#include <algorithm> // for std::reverse
#include <cstddef>   // for std::size_t
#include <iostream>
#include <string>

template<typename T>
class disp_bitset
{
    std::size_t _size;
    T _n;
public:
    explicit disp_bitset(std::size_t size, T n): _size(size), _n(n) {}
    friend std::ostream& operator<<(std::ostream& os, const disp_bitset& rhs)
    {
        T tmp = rhs._n;
        std::string aux;
        for (std::size_t i = 0; i < rhs._size; ++i)
        {
            aux += (tmp & 0x01) + '0';
            tmp >>= 1;
        }
        std::reverse(aux.begin(), aux.end());
        return os << aux;
    }
};

int main()
{
    disp_bitset<std::size_t> x(8, 41); // size_t 41 on 8 bits
    std::cout << x << std::endl;
    std::cout << disp_bitset<char>(16, 'a') << std::endl; // 'a' on 16 bits
}
