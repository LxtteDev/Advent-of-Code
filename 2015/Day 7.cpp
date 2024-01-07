// Advent of Code - 2015 - Day 7

#include <stdio.h>
#include <fstream>
#include <error.h>
#include <string>
#include <vector>
#include <regex>
#include <tuple>
#include <map>

std::regex mainRegex("([a-z0-9]{1,}) (AND|OR|RSHIFT|LSHIFT) ([a-z0-9]+) (->) ([a-z]+)");
std::regex notRegex("(NOT) ([a-z0-9]+) (->) ([a-z]+)");
std::regex setRegex("([a-z0-9]+) (->) ([a-z]+)");

enum Gates {
    AND,
    OR,
    NOT,
    LSHIFT,
    RSHIFT,
    SET
};

std::map<Gates, std::string> gatesStrings {
    { Gates::AND, "AND" },
    { Gates::OR, "OR" },
    { Gates::NOT, "NOT" },
    { Gates::LSHIFT, "LEFT SHIFT" },
    { Gates::RSHIFT, "RIGHT SHIFT" },
    { Gates::SET, "SET" }
};

typedef std::tuple<Gates, std::string, std::string> Operation;
typedef std::map<std::string, Operation> Operations;

std::map<std::string, unsigned short> registers;

Gates stringToGate(std::string gate) {
    if (gate == "AND") return Gates::AND;
    else if (gate == "OR") return Gates::OR;
    else if (gate == "NOT") return Gates::NOT;
    else if (gate == "LSHIFT") return Gates::LSHIFT;
    else if (gate == "RSHIFT") return Gates::RSHIFT;
    return Gates::SET;
}

// Parse Data
Operations getOperations() {
    Operations operations;
    std::ifstream operationsFile("2015/Day 7.txt");

    std::string line;
    while (std::getline( operationsFile, line )) {
        std::smatch matches;

        if (std::regex_search(line, matches, mainRegex)) {
            Gates gate = stringToGate(matches[2].str());
            Operation operation = std::make_tuple(gate, matches[1].str(), matches[3].str());

            operations[matches[5].str()] = operation; 
        } else if (std::regex_search(line, matches, notRegex)) {
            Operation operation = std::make_tuple(Gates::NOT, matches[2].str(), std::string());

            operations[matches[4].str()] = operation;
        } else if (std::regex_search(line, matches, setRegex)) {
            Operation operation = std::make_tuple(Gates::SET, matches[1].str(), std::string());

            operations[matches[3].str()] = operation;
        } else
            printf("Errors found when parsing \"%s\"\n", line.c_str());
    }

    return operations;
}

bool isInt(std::string string) {
    try {
        unsigned long position;
        std::stoi(string, &position);
        return position == string.size();
    } catch (...) {
        return false;
    }
}

unsigned short getValue(std::string reg) {
    if (isInt(reg)) return std::stoi(reg);
    if (registers.find(reg) != registers.end()) return registers[reg];
    registers[reg] = 0;
    return 0;
}   

unsigned short traceOperation(Operations& operations, std::string reg) {
    if (reg == "") return 0;
    if (registers.find(reg) != registers.end()) return registers[reg];

    Operation operation = operations[reg];

    Gates gate = std::get<0>(operation);
    std::string left = std::get<1>(operation);
    std::string right = std::get<2>(operation);

    unsigned short lValue = isInt(left) ? std::stoi(left) : traceOperation(operations, left);
    unsigned short rValue = isInt(right) ? std::stoi(right) : traceOperation(operations, right);

    if (!isInt(left)) registers[left] = lValue;
    if (!isInt(right)) registers[right] = rValue;

    if (gate == Gates::AND) return lValue & rValue;
    else if (gate == Gates::OR) return lValue | rValue;
    else if (gate == Gates::NOT) return ~lValue;
    else if (gate == Gates::LSHIFT) return lValue << rValue;
    else if (gate == Gates::RSHIFT) return lValue >> rValue;
    else if (gate == Gates::SET) return lValue;

    printf("Operation %s not yet implemented.\n", gatesStrings[gate].c_str());
    return 0;
}

int main(int, char**) {
    Operations operations = getOperations();

    // Part One
    unsigned short value = traceOperation(operations, std::string("a"));

    printf("Wire `a` contains the value %u\n", value);

    // Part Two
    registers.clear();
    registers["b"] = value;

    unsigned short newValue = traceOperation(operations, std::string("a"));

    printf("Wire `a` now contains the value %u\n\n", newValue);
}

