// std::vector of std::vector of ...

#include <iostream>
#include <vector>

int main() {
    int M = 3, N = 4;
    // memory allocation
    std::vector<std::vector<std::vector<double>>> arr(
        2, std::vector<std::vector<double>>(M, std::vector<double>(N)));

    std::size_t cnt{};
    for (int i = 0; i < 1; ++i)
        for (int j = 0; j < M; ++j)
            for (int k = 0; k < N; ++k)
                arr[i][j][k] = cnt++;

    for (int i = 0; i < 1; ++i)
        for (int j = 0; j < M; ++j)
            for (int k = 0; k < N; ++k)
                std::cout << arr[i][j][k] << " ";

    std::cout << std::endl;
}
