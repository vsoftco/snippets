// Finding the endianness of the platform, take 2

#include <iostream>
#include <cstdint>

bool is_little_endian()
{
    volatile union 
    {
        uint32_t i;
        unsigned char c[4];
    } e { 0x01234567 };

    return (e.c[0] - 0x67 == 0);
}

int main(void)
{
    std::cout << "System is " << (is_little_endian() ? "little " : "big ");
    std::cout << "endian." << std::endl;
}
