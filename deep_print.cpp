// Recursive print of STL-like containers of containers of ...

#include <fstream>
#include <iostream>
#include <list>
#include <vector>

template <class T>
void pretty_print(const T& arg, std::string delim, std::string left_separator,
                  std::string right_separator, std::ostream& os) {
    (void)delim, (void)left_separator, (void)right_separator;
    os << arg;
}

template <template <typename, typename> class Cont, typename T, typename Alloc>
void pretty_print(const Cont<T, Alloc>& arg, std::string delim = " ",
                  std::string left_separator = "[",
                  std::string right_separator = "]",
                  std::ostream& os = std::cout) {
    os << left_separator;
    bool first = true;
    for (auto&& elem : arg) {
        if (first) {
            first = false;
        } else {
            os << delim;
        }
        pretty_print(elem, delim, left_separator, right_separator, os);
    }
    os << right_separator;
}

int main() // usage examples
{
    std::vector<int> vint{1, 2, 3, 4};
    std::vector<std::vector<std::vector<int>>> vvint{{{1, 2, 3}, {4, 5}},
                                                     {{10, 20}, {7}, {9}}};
    std::list<std::vector<double>> lvdouble{{1.1, 2.2, 3.3}, {4.4, 5.5}};

    pretty_print(vint);
    std::cout << std::endl;

    pretty_print(vvint, ", ");
    std::cout << std::endl;

    pretty_print(lvdouble);
    std::cout << std::endl;

    std::ofstream fout("out.txt");
    pretty_print(lvdouble, " ", "{", "}", fout);
}
