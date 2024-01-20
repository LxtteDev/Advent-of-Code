// Advent of Code - 2015 - Day 19

#include <stdio.h>
#include <fstream>
#include <string>
#include <vector>
#include <tuple>
#include <regex>
#include <map>
#include <set>

std::regex replacmentsRegex("([A-Za-z]{1,2}) => ([A-Za-z]+)");

typedef std::vector<std::string> Possibilities;
typedef std::map<std::string, Possibilities> Replacments;
typedef std::tuple<std::string, Replacments> Data;

// Parse Data
Data generateData() {
    Replacments replacments;
    std::string input;
    std::ifstream dataFile("2015/Day 19.txt");

    std::string line;
    while (std::getline( dataFile, line )) {
        std::smatch matches;

        if (std::regex_search(line, matches, replacmentsRegex)) {
            std::string element = matches[1].str();
            std::string replacment = matches[2].str();

            if (replacments.find(element) == replacments.end()) replacments[element] = {};
            replacments[element].push_back(replacment);
        } else if (line.length() > 0) input = line;
    }

    return std::make_tuple( input, replacments );
}

int main(int, char**) {
    Data data = generateData();
    std::string input = std::get<0>(data);
    Replacments replacments = std::get<1>(data);

    // Part One
    std::set<std::string> distinctMolecules;
    std::vector<std::string> molecules;

    for (unsigned int i = 0; i < input.length(); i++) {
        char first = input[i];
        if (islower(first)) continue;

        std::string element = std::string(1, first);
        if (i < input.length() - 1 && islower(input[i + 1])) element += std::string(1, input[i + 1]);

        if (replacments.find(element) == replacments.end()) continue;

        Possibilities possibilities = replacments[element];
        for (unsigned int j = 0; j < possibilities.size(); j++) {
            std::string replacment = input;
            replacment.replace(i, element.length(), possibilities[j]);

            if (distinctMolecules.insert(replacment).second)
                molecules.push_back(replacment);
        }
    }

    printf("Found %zu unique molecules after one replacement.\n", molecules.size());

    // Part Two
    std::string replacment = input;
    int steps = 0;

    while (replacment != "e") {
        for (Replacments::iterator i = replacments.begin(); i != replacments.end(); i++) {
            for (unsigned int j = 0; j < i->second.size(); j++) {
                size_t position = replacment.find(i->second[j]);

                if (position != std::string::npos) {
                    replacment.replace(position, i->second[j].size(), i->first);
                    steps++;
                    break;
                }
            }
        }
    }

    printf("A minimum of %i steps are required to make the medicine.\n\n", steps);
}