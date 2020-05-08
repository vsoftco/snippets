// Finding the endianness of the platform, take 2

#include <cstdint>
#include <iostream>

bool is_little_endian() {
  volatile union {
    uint32_t i;
    unsigned char c[4];
  } e{0x01234567}; // initializes the first member, i.e. i is active
  // it's undefined behavior to read from the member of the union
  // that wasn't most recently written. Many compilers implement,
  // as a non-standard language extension, the ability to read
  // inactive members of a union. (cppreference.com)
  return (e.c[0] - 0x67 == 0);
}

int main(void) {
  std::cout << "System is " << (is_little_endian() ? "little " : "big ");
  std::cout << "endian." << std::endl;
}
