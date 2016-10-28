// Display an arbitrary iterable container in pretty format

#include <iostream>
#include <type_traits>
#include <vector>

// used in SFINAE, future std::void_t
template<typename ...>
using to_void = void;

// iterable type trait
template<typename T, typename = void>
struct is_iterable : std::false_type {};

// specialization for iterables
template<typename T>
struct is_iterable<T,
        to_void<decltype(std::declval<T>().begin()),
                decltype(std::declval<T>().end()),
                typename T::value_type>
        > : std::true_type {};

// we need to SFINAE only iterable types, otherwise we get an ambiguity
// when displying fundamental types inside operator<<              
template<typename C>
typename std::enable_if<is_iterable<C>::value, std::ostream&>::type
operator<<(std::ostream& s, const C& v) {
    // nice trick from 
    // http://en.cppreference.com/w/cpp/container/vector/vector#Example
    s.put('[');
    char comma[3] = {'\0', ' ', '\0'}; 
    for (const auto& e : v) {
        s << comma << e;
        comma[0] = ',';
    }
    return s << ']';
}

int main()
{
    std::vector<int> vi{1, 2, 3, 4};
    std::cout << vi;
}
