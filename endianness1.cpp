// Finding the endianness of the platform, take 1

#include <cstdint>

int main() {
    volatile uint32_t i = 0x01234567;
    // return 0 for big endian, 1 for little endian.
    return (*((uint8_t*) (&i))) == 0x67;
}