// Average with std::accumulate and a lambda

#include <algorithm>
#include <iostream>
#include <vector>

int main() {
    std::vector<int> v = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    auto lambda = [&v](double a, double b) { return a + b / v.size(); };
    auto avg = std::accumulate(v.begin(), v.end(), 0.0, lambda);
    std::cout << avg << std::endl;
}
