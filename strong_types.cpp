// Strong (opaque) types

#include <iostream>
#include <utility>

template <typename T, int N> // N is used for "tagging" the type
struct strong_typedef
{
    using strong_type = strong_typedef<T, N>; // typedef for the strong type
    using type = T; // the wrapped type
    T value{}; // the  wrapped value, zero by default

    strong_typedef() = default;
    strong_typedef(const T& x): value(x) {};
    // copy ctors and assignment operators are defaulted

    // relational operators
    bool operator==(const strong_type& x) const
    {
        return  value == x.value;
    }
    bool operator<(const strong_type& x) const
    {
        return value < x.value;
    }
    // the rest  are automatically implemented via
    // using namespace std::rel_ops in main()

    // Arithmetic operators
    strong_type& operator++()
    {
        ++value;
        return *this;
    }
    strong_type operator++(int) // postfix
    {
        strong_type tmp(*this);
        ++*this;
        return tmp;
    }
    strong_type& operator--()
    {
        --value;
        return *this;
    }
    strong_type operator--(int) // postfix
    {
        strong_type tmp(*this);
        --*this;
        return tmp;
    }

    strong_type& operator+=(const strong_type& rhs)
    {
        value += rhs.value;
        return *this;
    }
    strong_type& operator-=(const strong_type& rhs)
    {
        value -= rhs.value;
        return *this;
    }
    strong_type& operator*=(const strong_type& rhs)
    {
        value *= rhs.value;
        return *this;
    }
    strong_type& operator/=(const strong_type& rhs)
    {
        value /= rhs.value;
        return *this;
    }

    friend std::ostream& operator<<(std::ostream& lhs, 
            const strong_typedef& rhs)
    {
        lhs << rhs.value;
        return lhs;
    }

    friend std::istream& operator>>(std::istream& lhs, strong_typedef& rhs)
    {
        lhs >> rhs.value;
        return lhs;
    }
};

template<typename T, int N>
strong_typedef<T, N>
operator+(strong_typedef<T, N> lhs, const strong_typedef<T, N>& rhs)
{
    lhs += rhs;
    return lhs;
}

template<typename T, int N>
strong_typedef<T, N>
operator-(strong_typedef<T, N> lhs, const strong_typedef<T, N>& rhs)
{
    lhs -= rhs;
    return lhs;
}

template<typename T, int N>
strong_typedef<T, N>
operator*(strong_typedef<T, N> lhs, const strong_typedef<T, N>& rhs)
{
    lhs *= rhs;
    return lhs;
}

template<typename T, int N>
strong_typedef<T, N>
operator/(strong_typedef<T, N> lhs, const strong_typedef<T, N>& rhs)
{
    lhs /= rhs;
    return lhs;
}

int main()
{
    using namespace std::rel_ops;

    strong_typedef<double, 0> x, y;
    x = 10;
    y = 21;
    //y = x;
    std::cout << std::boolalpha << (y == x) << std::endl;
    std::cout << (x / y) << std::endl;
    std::cout << (strong_typedef<double, 0>(10) >= x) << std::endl;

    strong_typedef<double, 1> z;
    std::cin >> z;
    std::cout << z << std::endl;
    // z + x; // won't compile, type violation
}
