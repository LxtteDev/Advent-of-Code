// Advent of Code - 2015 - Day 16

#include <stdio.h>
#include <fstream>
#include <string>
#include <vector>
#include <regex>
#include <map>

std::regex itemsRegex("(children|cats|goldfish|trees|cars|perfumes|samoyeds|pomeranians|akitas|vizslas): ([0-9]+)");

typedef std::map<std::string, int> Aunt;
typedef std::vector<Aunt> Aunts;

Aunt items = {
    { "children", 3 },
    { "cats", 7 },
    { "samoyeds", 2 },
    { "pomeranians", 3 },
    { "akitas", 0 },
    { "vizslas", 0 },
    { "goldfish", 5 },
    { "trees", 3 },
    { "cars", 2 },
    { "perfumes", 1 }
};

// Parse Data
Aunts getAunts() {
    Aunts aunts;
    std::ifstream listFile("2015/Day 16.txt");

    std::string line;
    while (std::getline( listFile, line )) {
        std::smatch matches;
        Aunt aunt;

        while (std::regex_search(line, matches, itemsRegex)) {
            aunt[matches[1].str()] = std::stoi(matches[2].str());
            line = matches.suffix().str();
        }

        aunts.push_back(aunt);
    }

    return aunts;
}

bool hasItem(Aunt& aunt, std::string item, int count, bool part = false) {
    if (!part && aunt.find(item) == aunt.end()) return true;

    if (part)
        if (item == "cats" || item == "trees") return aunt[item] > count;
        else if (item == "pomeranians" || item == "goldfish") return aunt[item] < count;

    return aunt[item] == count;
}

int main(int, char**) {
    Aunts aunts = getAunts();

    // Part one
    unsigned int aunt = 500;
    for (unsigned int i = 0; i < aunts.size(); i++) {
        bool valid = true;
        for (Aunt::iterator j = aunts[i].begin(); j != aunts[i].end(); ++j)
            valid = valid && hasItem(aunts[i], j->first, items[j->first]);
        if (valid) { aunt = i; break; }
    }

    printf("The card was thought to be sent by Aunt Sue %u.\n", aunt + 1);

    // Part two
    aunt = 500;
    for (unsigned int i = 0; i < aunts.size(); i++) {
        bool valid = true;
        for (Aunt::iterator j = aunts[i].begin(); j != aunts[i].end(); ++j)
            valid = valid && hasItem(aunts[i], j->first, items[j->first], true);
        if (valid) { aunt = i; break; }
    }

    printf("The card was really sent by Aunt Sue %u.\n\n", aunt + 1);
}

