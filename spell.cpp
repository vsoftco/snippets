// Spells the input using the NATO phonetic alphabet

/* Possible usage scenarios:
 
 spell # spells from the console, end with CTRL+D (UNIX) or CTRL+Z (Windows)
 spell "text"
 cat file | spell

*/

#include <cctype>
#include <cstdlib>
#include <iostream>
#include <unordered_map>

void spell(std::string const& str,
           std::unordered_map<char, std::string> const& dict)
{
    for (auto && elem : str)
    {
        std::cout << elem;
        if (dict.find(std::toupper(elem)) != dict.end())
            std::cout << " - " << dict.at(std::toupper(elem));
        std::cout << std::endl;
    }
}

int main(int argc, char** argv)
{
    std::unordered_map<char, std::string> dict;
    // Convention: use capital letters for the keys
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
        std::cerr << "Usage: " << argv[0] << " [text]\n";
        std::exit(EXIT_FAILURE);
    }

    std::string str;
    if (argc == 1) // spells from the standard input
    {
        while (std::getline(std::cin, str))
        {
            spell(str, dict);
        }
    }
    else // spells specifed text
    {
        spell(argv[1], dict);
    }
}
