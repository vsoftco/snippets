// Displaying comma-separated-value files

#include <algorithm>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

int main(int argc, char **argv) {
  if (argc != 2) {
    std::cout << "Usage: " << argv[0] << " <filename.csv>" << std::endl;
    std::exit(EXIT_FAILURE);
  }

  std::ifstream fin(argv[1]);
  if (!fin.is_open()) {
    std::cout << "Can not open the file <" << argv[1] << ">" << std::endl;
    std::exit(EXIT_FAILURE);
  }

  std::string str;
  while (std::getline(fin, str)) {
    std::istringstream iss(str);
    std::string token;
    while (std::getline(iss, token, ',')) {
      // remove extra junk (punctuation etc)
      token.erase(std::remove_if(token.begin(), token.end(),
                                 [](char &c) {
                                   // return !isalnum(c);
                                   // return !isdigit(c);
                                   return c == ' '; // remove extra spaces
                                 }),
                  token.end());
      std::cout << token << " ";
    }
    std::cout << std::endl;
  }
}