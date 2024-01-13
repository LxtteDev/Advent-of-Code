// Advent of Code - 2015 - Day 12

#include <algorithm>
#include <stdio.h>
#include <fstream>
#include <string>
#include <vector>
#include <regex>
#include <tuple>
#include <map>
#include <set>

std::regex happinessRegex("([a-zA-Z]+) .+ (gain|lose) ([0-9]+) .+ ([a-zA-Z]+)");

typedef std::map<std::string, std::map<std::string, int>> Chart;
typedef std::tuple<Chart, std::vector<std::string>> ChartData;

// Parse Data
ChartData getChart() {
    Chart chart;
    std::set<std::string> namesSet;
    std::vector<std::string> names;
    std::ifstream listFile("2015/Day 13.txt");

    std::string line;
    while (std::getline( listFile, line )) {
        std::smatch matches;

        if (std::regex_search(line, matches, happinessRegex)) {
            if (chart.find(matches[1].str()) == chart.end()) chart[matches[1].str()] = {};
            if (namesSet.insert(matches[1].str()).second) names.push_back(matches[1].str());
            if (namesSet.insert(matches[4].str()).second) names.push_back(matches[4].str());

            int happiness = std::stoi(matches[3].str());

            chart[matches[1].str()][matches[4].str()] = matches[2] == "lose" ? -1 * happiness : happiness;
        }
    }

    ChartData data = std::make_tuple(chart, names);
    return data;
}

int main(int, char**) {
    ChartData data = getChart();
    Chart chart = std::get<0>(data);
    std::vector<std::string> names = std::get<1>(data);

    // Part one
    int happiness = 0;

    while (std::next_permutation(names.begin(), names.end())) {
        int totalHappiness = 0;

        for (int i = 0; i < (int)(names.size()); i++) {
            std::string name = names[i];

            std::string left = names[(i - 1) < 0 ? ((int)(names.size()) - 1) : (i - 1)];
            std::string right = names[(i + 1) > ((int)(names.size()) - 1) ? 0 : (i + 1)];

            totalHappiness += chart[name][left] + chart[name][right];
        }

        if (totalHappiness > happiness) happiness = totalHappiness;
    }

    printf("The optial seating arrangement results in %i happiness.\n", happiness);

    // Part two
    happiness = 0;

    names.push_back("");
    while (std::next_permutation(names.begin(), names.end())) {
        int totalHappiness = 0;

        for (int i = 0; i < (int)(names.size()); i++) {
            std::string name = names[i];
            if (name == "") continue;

            std::string left = names[(i - 1) < 0 ? ((int)(names.size()) - 1) : (i - 1)];
            std::string right = names[(i + 1) > ((int)(names.size()) - 1) ? 0 : (i + 1)];

            totalHappiness += (left == "" ? 0 : chart[name][left]) + (right == "" ? 0 : chart[name][right]);
        }

        if (totalHappiness > happiness) happiness = totalHappiness;
    }

    printf("The new optial seating arrangement results in %i happiness.\n\n", happiness);
}

