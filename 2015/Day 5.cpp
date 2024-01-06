// Advent of Code - 2015 - Day 5

#include <stdio.h>
#include <fstream>
#include <string>
#include <vector>
#include <regex>

// Regex
std::regex vowels("[aeiou]");
std::regex multiple("(.)\\1");
std::regex multipleGroup("(\\w{2})[\\w\\b]*\\1");
std::regex banned("(ab)|(cd)|(pq)|(xy)");
std::regex oneHop("(\\w)[a-z\\b]\\1");

// Parse Data
std::vector<std::string> getStrings() {
    std::vector<std::string> strings;
    std::ifstream stringsFile("2015/Day 5.txt");

    std::string line;
    while (std::getline(stringsFile, line)) {
        strings.push_back(line);
    }

    return strings;
}

int main(int, char**) {
    std::vector<std::string> strings = getStrings();

    // Part One
    std::vector<std::string> niceStrings;

    for (unsigned int i = 0; i < strings.size(); i++) {
        std::string& string = strings[i];

        if (std::distance(std::sregex_iterator( string.begin(), string.end(), vowels ), std::sregex_iterator()) >= 3 &&
            std::regex_search( string, multiple ) &&
           !std::regex_search( string, banned ))
            niceStrings.push_back(string);
    }

    printf("The list contains %zu nice strings!\n", niceStrings.size());

    // Part Two
    std::vector<std::string> veryNiceStrings;

    for (unsigned int i = 0; i < strings.size(); i++) {
        std::string& string = strings[i];

        if (std::regex_search( string, multipleGroup ) &&
            std::regex_search( string, oneHop ))
            veryNiceStrings.push_back(string);
    }

    printf("The list contains %zu very nice strings!\n\n", veryNiceStrings.size());
}

