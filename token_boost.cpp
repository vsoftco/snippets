// Tokenizing using boost::tokenizer

#include <iostream>
#include <string>

#include <boost/tokenizer.hpp>

using separator = boost::char_separator<char>;
using tokenizer = boost::tokenizer<separator>;

int main() {
  std::string str = ";;Hello|world||-foo--bar;yow;baz|";
  tokenizer tokens(str, separator("-;|"));
  for (auto &&elem : tokens)
    std::cout << "<" << elem << "> ";
  std::cout << "\n";
}
