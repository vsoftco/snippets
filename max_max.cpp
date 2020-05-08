// Finds the largest and second largest values in a range

#include <algorithm>
#include <cassert>
#include <cstddef>
#include <iostream>
#include <iterator>
#include <list>

template <typename Iterator>
auto max_max(Iterator begin, Iterator end) {
    assert(std::distance(begin, end) >= 2);
    using T = typename std::iterator_traits<Iterator>::value_type;

    auto it = std::next(begin);
    std::pair<T, T> max = std::minmax(*begin, *it);
    while (++it != end) {
        if (*it > max.first) {
            if (*it > max.second) {
                max.first = max.second;
                max.second = *it;
            } else {
                max.first = *it;
            }
        }
    }

    return max;
}

int main() {
    std::list<int> v{10, -2, 15, 1, 204, -10, 17};

    auto result = max_max(std::begin(v), std::end(v));
    std::cout << result.first << ' ' << result.second;
}
