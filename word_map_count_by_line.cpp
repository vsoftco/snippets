// Given a text file, reads its contents and then returns a list
// of the words in the file along with the line number they appear on
// and the number of times that word appears on each line

// Asked on http://stackoverflow.com/q/29618503/3093378

#include <cstddef>
#include <iostream>
#include <map>
#include <sstream>
#include <string>

int main() {
  std::stringstream ifile("Foo Bar Vlad Vlad Bar\nBaz\nFoo Foo\nVlad");
  std::map<std::string, std::map<std::size_t, std::size_t>> word_map;

  // process the input stream
  std::string line;
  std::size_t line_no{0};
  while (std::getline(ifile, line)) {
    line_no++;
    // process the words in the current line
    std::istringstream ss(line);
    std::string word;
    while (ss >> word) {
      word_map[word][line_no]++;
    }
  }
  // now display it
  for (auto &&key : word_map) {
    std::cout << key.first << " -> ";
    for (auto &&value : key.second) {
      std::cout << value.first << ":" << value.second << " ";
    }
    std::cout << std::endl;
  }
}
