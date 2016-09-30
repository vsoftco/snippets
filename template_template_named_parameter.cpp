// One of the few instances when naming a template template parameter
// makes sense, although it cannot be accessed outside the template 
// argument list

#include <iostream>
#include <memory>
#include <vector>

// we use the first template template parameter name as 
// default argument to the second template template parameter
template<template<typename U, typename = std::allocator<U>> class T>
struct X
{
    T<int> member{};
};

// otherwise we need to explicitly specify the second 
// template template parameter
template<template<typename, typename> class T>
struct Y
{
    // won't compile
    // error: wrong number of template arguments (1, should be 2)
    // T<int> member{}; 
    T<int, std::allocator<int>> member{};
};


int main()
{
    X<std::vector> x;
    x.member.push_back(10);
    x.member.push_back(20);

    for(auto && elem: x.member)
        std::cout << elem << " ";
}
