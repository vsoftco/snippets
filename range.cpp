// Python-like simple range in C++14

#include <iostream>
#include <type_traits>

template<typename T>
class Range
{
private:
    T first, last, iter, step;
public:
    Range(T first, T last, T step = 1):
        first(first),
        last(last),
        iter(first),
        step(step)
    {}

    // Iterable functions
    const Range& begin() const noexcept { return *this; }
    const Range& end() const noexcept { return *this; }
    const Range& cbegin() const noexcept { return begin(); }
    const Range& cend() const noexcept { return end(); }

    // Iterator functions
    bool operator!=(const Range&) const noexcept { return iter < last; }
    Range& operator++() noexcept { iter += step; return *this;}
    Range operator++(int) noexcept { 
        Range cpy{*this}; this->operator++(); return cpy;}
    T operator*() const noexcept { return iter; }
};

// Convenience function for automatic type deduction
template<typename T>
auto make_range(T fist, T last, T step = 1)
{
    return Range<T>{fist, last, step};
}

int main()
{
    for (auto i : make_range(10, 20, 2))
    {
        std::cout << i << std::endl;
    }

    auto it = make_range(-0.5, 0.5, 0.1);
    std::cout << *(it++) << std::endl;
    std::cout << *(++it) << std::endl;
    std::cout << *it;
}
