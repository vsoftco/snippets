// Reverting words in a sentence, functional style

#include <algorithm>
#include <iostream>
#include <iterator>
#include <sstream>
#include <string>

int main() {
    std::stringstream input{"this is a test"};
    std::transform(std::istream_iterator<std::string>(input), {},
                   std::ostream_iterator<std::string>(std::cout, " "),
                   [](const std::string& str) {
                       return std::string{str.rbegin(), str.rend()};
                   }); // outputs "siht si a tset "
}