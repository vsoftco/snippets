// Recursive string to decimal base transformation in arbitrary base

#include <iostream>
#include <string>

int str_to_int(const std::string& str, std::size_t base) {
    if (str.size() == 0) {
        return 0;
    } else {
        return (str[str.size() - 1] - '0') +
               base * str_to_int(str.substr(0, str.size() - 1), base);
    }
}

int main() { std::cout << str_to_int("101101", 2) << std::endl; }