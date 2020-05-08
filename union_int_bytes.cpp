// Displaying the bytes in an int via a union

#include <iostream>

union U {
  unsigned char bytes[sizeof(int)];
  int x;
};

int main() {
  U u;
  u.x = 394783212;
  std::cout << std::showbase << std::uppercase << std::hex << u.x << std::endl;
  for (std::size_t i = 0; i < sizeof(int); ++i)
    std::cout << static_cast<int>(u.bytes[i]) << " ";
  std::cout << std::endl;
}
