// Partial sorting via a functor that uses a pointer to member

#include <algorithm>
#include <iomanip>
#include <iostream>
#include <vector>

template <typename T1, typename T2>
struct Functor
{
    T1 T2::* memPointer;
    Functor(T1 T2::* t): memPointer(t) {}
    bool operator() (const T2 &obj1, const T2 &obj)
    {
        return obj1.*memPointer < (obj.*memPointer);
    }
};

struct Foo
{
    double x;
    double y;
};

int main()
{
    std::vector<Foo> v{{9, 89}, {10, 10}, {5, 100}};

    std::cout << "Sorting by the first member x" << std::endl;
    Functor<double, Foo> by_x(&Foo::x);
    std::sort(v.begin(),  v.end(),  by_x);
    for (auto && elem : v)
        std::cout << std::setw(2) << elem.x << " -> " << elem.y << std::endl;

    std::cout << "Sorting by the second member y" << std::endl;
    Functor<double, Foo> by_y(&Foo::y);
    std::sort(v.begin(),  v.end(),  by_y);
    for (auto && elem : v)
        std::cout << std::setw(2) << elem.x << " -> " << elem.y << std::endl;
}
