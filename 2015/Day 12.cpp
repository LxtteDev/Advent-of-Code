// Advent of Code - 2015 - Day 12

#include <json/json.h>
#include <stdio.h>
#include <fstream>
#include <string>
#include <regex>

std::regex nubmersRegex("([\\-0-9]+)");

// Parse Data
std::string getList() {
    std::string output;
    std::ifstream listFile("2015/Day 12.txt");

    std::string line;
    while (std::getline( listFile, line ))
        output += line;

    return output;
}

int countList(Json::Value list) {
    int count = 0;

    if (list.isArray()) {
        for (unsigned int i = 0; i < list.size(); i++)
            if (list[i].isInt())
                count += list[i].asInt();
            else if (list[i].isObject() || list[i].isArray())
                count += countList(list[i]);
    } else {
        for (Json::Value::iterator iterator = list.begin(); iterator != list.end(); ++iterator) {
            std::string key = iterator.key().asString();
            if (list[key].isString() && list[key].asString() == "red") return 0;

            if (list[key].isInt()) count += list[key].asInt();
            else count += countList(list[key]);
        }
    }

    return count;
}

int main(int, char**) {
    std::string input = getList();

    // Part one
    int total = 0;

    for (std::sregex_iterator iterator = std::sregex_iterator(input.begin(), input.end(), nubmersRegex); iterator != std::sregex_iterator(); ++iterator)
        total += std::stoi((*iterator).str());

    printf("The numbers in the list add up to %i.\n", total);

    // Part two
    Json::Value list;
    Json::Reader reader;
    bool parsingSuccessful = reader.parse(input, list);
    if ( !parsingSuccessful ) printf("Error parsing json\n");

    total = countList(list);

    printf("All numbers in the new list add up to %i.\n\n", total);
}

