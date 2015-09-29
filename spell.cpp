// Spells the input using the phonetic alphabet
// Usage: spell (end the program with CTRL+D on UNIX, CTRL+Z on Windows)
// Usage: cat file | spell

#include <cctype>
#include <iostream>
#include <map>

int main()
{
    std::map<char, std::string> dict;
    dict['A'] = "Alpha";  dict['B'] = "Bravo";    dict['C'] = "Charlie";
    dict['D'] = "Delta";  dict['E'] = "Echo";     dict['F'] = "Foxtrot";
    dict['G'] = "Golf";   dict['H'] = "Hotel";    dict['I'] = "India";
    dict['J'] = "Juliet"; dict['K'] = "Kilo";     dict['L'] = "Lima";
    dict['M'] = "Mike";   dict['N'] = "November"; dict['O'] = "Oscar";
    dict['P'] = "Papa";   dict['Q'] = "Quebec";   dict['R'] = "Romeo";
    dict['S'] = "Sierra"; dict['T'] = "Tango";    dict['U'] = "Uniform";
    dict['V'] = "Victor"; dict['W'] = "Whiskey";  dict['X'] = "X-ray";
    dict['Y'] = "Yankee"; dict['Z'] = "Zulu";

    for (char elem; std::cin >> elem; )
    {
        std::cout << elem;
        if (std::isalpha(elem))
            std::cout << " - " << dict[std::toupper(elem)];
        std::cout << std::endl;
    }
}