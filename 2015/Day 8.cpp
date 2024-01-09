// Advent of Code - 2015 - Day 8

#include <stdio.h>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <regex>

typedef std::vector<std::string> List;

std::regex escapeRegex("(\\\\)([\\\\\"])|(\\\\x)([a-fA-F0-9]{2})");
std::regex encodeRegex("[\"\\\\]");

// Parse Data
List getList() {
    List list;
    std::ifstream listFile("2015/Day 8.txt");

    std::string line;
    while (std::getline( listFile, line ))
        list.push_back(line);

    return list;
}

int main(int, char**) {
    List list = getList();

    int difference = 0;
    int newChars = 0;

    for (unsigned int i = 0; i < list.size(); i++) {
        std::string string = list[i];

        std::stringstream escape;
        std::regex_replace(std::ostreambuf_iterator<char>(escape), string.begin() + 1, string.end() - 1, escapeRegex, "_");

        difference += string.length() - escape.str().length();

        int encodes = std::distance( std::sregex_iterator(string.begin(), string.end(), encodeRegex), std::sregex_iterator() );
        newChars += encodes + 2;
    }

    // Part One
    printf("There are %i characters in the list.\n", difference);

    // Part Two
    printf("%i new characters are added after encoding.\n\n", newChars);
}

