// Case-insensitive strings via changing the char trait
// Example taken from http://en.cppreference.com/w/cpp/string/char_traits
// which got it from http://www.gotw.ca/gotw/029.htm

#include <cctype>
#include <cstddef>
#include <iostream>
#include <string>

struct ci_char_traits : public std::char_traits<char>
{
    static bool eq(char c1, char c2) {return ::toupper(c1) == ::toupper(c2);}
    static bool ne(char c1, char c2) {return ::toupper(c1) != ::toupper(c2);}
    static bool lt(char c1, char c2) {return ::toupper(c1) <  ::toupper(c2);}
    static int compare(const char* s1, const char* s2, std::size_t n)
    {
        while ( n-- != 0 )
        {
            if ( ::toupper(*s1) < ::toupper(*s2) ) return -1;
            if ( ::toupper(*s1) > ::toupper(*s2) ) return 1;
            ++s1; ++s2;
        }
        return 0;
    }
    static const char* find(const char* s, int n, char a)
    {
        while ( n-- > 0 && ::toupper(*s) != ::toupper(a) )
        {
            ++s;
        }
        return s;
    }
};

// case-insensitive string
using ci_string = std::basic_string<char, ci_char_traits>;

// need to overwrite the insertion and extraction operators
std::ostream& operator<<(std::ostream& os, const ci_string& str)
{
    return os.write(str.data(), str.size());
}

std::istream& operator>>(std::istream& os, ci_string& str)
{
    std::string tmp;
    os >> tmp;
    str.assign(tmp.data(), tmp.size());
    return os;
}

int main()
{
    ci_string s1{"Test"}, s2{"test"};
    std::cout << std::boolalpha << (s1 == s2) << std::endl;

    ci_string str;
    std::cin >> str;
    std::cout << str << std::endl;
}