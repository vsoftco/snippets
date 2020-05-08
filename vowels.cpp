// Count the vowels in a string

#include <cstddef>
#include <iostream>
#include <map>
#include <string>

int main() {
    std::map<char, std::size_t> m;
    std::string s{"This is some test with vowels"};

    for (auto x : s)
        ++m[x];

    std::cout << "a: " << m['a'] << std::endl;
    std::cout << "e: " << m['e'] << std::endl;
    std::cout << "i: " << m['i'] << std::endl;
    std::cout << "o: " << m['o'] << std::endl;
    std::cout << "u: " << m['u'] << std::endl;
}
