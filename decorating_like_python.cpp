// Decorating a function, Python style

#include <iostream>

template<class T>
auto decorator(T&& func)
{
    auto new_function = [func{std::forward<T>(func)}](auto && ... args)
    {
        std::cout << "BEGIN decorating...\n";
        auto result = func(std::forward<decltype(args)>(args)...);
        std::cout << "END decorating\n";
        return result;
    };
    return new_function;
}

// we will decorate this function
int f(int x, int y)
{
    std::cout << x * y << '\n';
    return x * y;
}

int main()
{
    auto decorated = decorator(f);
    auto triple_decorated = decorator(decorator(decorator(f)));

    decorated(5, 10);
    triple_decorated(10, 20);
}
