// Spells the input using the NATO phonetic alphabet

// Possible usage scenarios:
// spell file.txt
// spell  # end the program with CTRL+D on UNIX, CTRL+Z on Windows
// cat file | spell
// echo "Text" | spell

#include <cctype>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <unordered_map>

void spell(std::string const& str,
           std::unordered_map<char, std::string> const& dict)
{
    for (auto && elem : str)
    {
        std::cout << elem;
        if (std::isalpha(elem))
            std::cout << " - " << dict.at(std::toupper(elem));
        std::cout << '\n';
    }
}

int main(int argc, char** argv)
{
    std::unordered_map<char, std::string> dict;
    dict['A'] = "Alpha";  dict['B'] = "Bravo";    dict['C'] = "Charlie";
    dict['D'] = "Delta";  dict['E'] = "Echo";     dict['F'] = "Foxtrot";
    dict['G'] = "Golf";   dict['H'] = "Hotel";    dict['I'] = "India";
    dict['J'] = "Juliet"; dict['K'] = "Kilo";     dict['L'] = "Lima";
    dict['M'] = "Mike";   dict['N'] = "November"; dict['O'] = "Oscar";
    dict['P'] = "Papa";   dict['Q'] = "Quebec";   dict['R'] = "Romeo";
    dict['S'] = "Sierra"; dict['T'] = "Tango";    dict['U'] = "Uniform";
    dict['V'] = "Victor"; dict['W'] = "Whiskey";  dict['X'] = "X-ray";
    dict['Y'] = "Yankee"; dict['Z'] = "Zulu";

    if (argc > 2)
    {
        std::cout << "Usage: " << argv[0] << " [file]\n";
        std::exit(EXIT_FAILURE);
    }

    std::string str;
    if (argc == 1) // pipe input
    {
        while (std::getline(std::cin, str))
        {
            spell(str, dict);
        }
    }
    else // file input
    {
        std::ifstream ifile{argv[1]};
        if (!ifile)
        {
            std::cout << "Cannot open the input file [" << argv[1] << "]\n";
            std::exit(EXIT_FAILURE);
        }
        while (std::getline(ifile, str))
        {
            spell(str, dict);
        }
    }
}