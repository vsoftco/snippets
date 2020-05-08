// Replicate a vector

#include <cstddef>
#include <iostream>
#include <vector>

template <class T>
std::vector<T> replicate(const std::vector<T> &v, std::size_t reps) {
  std::vector<T> result(reps * v.size());
  for (std::size_t i = 0; i < reps; ++i)
    std::copy(v.begin(), v.end(), result.begin() + i * v.size());
  return result;
}

int main() {
  std::vector<int> v{1, 2, 3};
  for (auto &&elem : replicate(v, 4))
    std::cout << elem << " ";
}
