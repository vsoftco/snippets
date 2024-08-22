// Variadic print, take 2

#include <iostream>
#include <stdexcept>

void print(const char* s) {
    while (s && *s) {
        if (*s == '%' && *++s != '%') {
            // make sure that there wasn't meant to be more arguments
            // %% represents plain % in a format string
            throw std::runtime_error("invalid format: missing arguments");
        }
        std::cout << *s++;
    }
}

template <typename T, typename... Args>          // note the "..."
void print(const char* s, T value, Args... args) // note the "..."
{
    while (s && *s) {
        if (*s == '%' &&
            *++s != '%') {      // a format specifier (ignore which one it is)
            std::cout << value; // use first non-format argument
            return print(++s, args...); // "peel off" first argument
        }
        std::cout << *s++;
    }
    throw std::runtime_error("extra arguments provided to printf");
}

int main() { print("OK %d test", 10); }
