// Expression SFINAE via detect
// checks wether a class has a specific member function
// From: http://stackoverflow.com/a/35349163/3093378

#include <type_traits>
#include <utility>

struct Foo
{
    void ham() {}
    void ham() const {}
};

struct Bar
{
    void ham() {}
};

template <typename...>
using void_t = void;

template <template <typename> class D, typename T, typename = void>
struct detect : std::false_type {};

template <template <typename> class D, typename T>
struct detect<D, T, void_t<D<T>>> : std::true_type {};

// expression SFINAE failure when T = bar
// const_ham<Bar> is be ill-formed, so the detect specialization is not chosen
template <typename T> 
using const_ham = decltype(std::declval<const T&>().ham());

int main()
{
    static_assert(detect<const_ham, Foo>::value, "!");
    static_assert(!detect<const_ham, Bar>::value, "!");
}