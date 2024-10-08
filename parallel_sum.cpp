// Parallel sum via std::thread

#include <algorithm>
#include <future>
#include <iostream>
#include <numeric>
#include <vector>

template <typename RAIter>
int parallel_sum(RAIter beg, RAIter end) {
    auto len = std::distance(beg, end);
    if (len < 1000) {
        return std::accumulate(beg, end, 0);
    }

    RAIter mid = beg + len / 2;
    auto handle =
        std::async(std::launch::async, parallel_sum<RAIter>, mid, end);
    int sum = parallel_sum(beg, mid);
    return sum + handle.get();
}

int main() {
    std::vector<int> v(10000, 1);
    std::cout << "The sum is " << parallel_sum(v.begin(), v.end()) << '\n';
}