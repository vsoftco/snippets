// Type trait that computes the length of a type list
// Essentially an implementation of sizeof... operator

#include <iostream>

template<typename Head, typename... Args>
struct lenght_type_list
{
    const static size_t length = 1 + lenght_type_list<Args...>::length;
};

template<typename Head>
struct lenght_type_list<Head>
{
    const static size_t length = 1;
};

int main()
{
    std::cout << lenght_type_list<int, double, float>::length; // prints 3
}
