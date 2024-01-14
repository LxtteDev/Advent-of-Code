// Advent of Code - 2015 - Day 14

#include <algorithm>
#include <stdio.h>
#include <fstream>
#include <string>
#include <vector>
#include <regex>
#include <tuple>
#include <map>

std::regex raceRegex("([a-zA-Z]+) .+ ([0-9]+) .+ ([0-9]+) .+ ([0-9]+)");

typedef std::tuple<std::string, int, int, int> Raindeer;
typedef std::vector<Raindeer> Raindeers;

// Parse Data
Raindeers getRaindeers() {
    Raindeers raindeers;
    std::ifstream listFile("2015/Day 14.txt");

    std::string line;
    while (std::getline( listFile, line )) {
        std::smatch matches;

        if (std::regex_search(line, matches, raceRegex)) {
            Raindeer raindeer = std::make_tuple(matches[1].str(), std::stoi(matches[2].str()), std::stoi(matches[3].str()), std::stoi(matches[4].str()));
            raindeers.push_back(raindeer);
        }
    }

    return raindeers;
}

int calculateDistance(Raindeer raindeer, int time) {
    int distance = 0;
    bool resting = false;

    int speed = std::get<1>(raindeer);
    int count = std::get<2>(raindeer);
    int rest = std::get<3>(raindeer);

    while (true) {
        if (time <= 0) break;

        if (resting) {
            if (time < rest) time = 0;
            else time -= rest;
        } else {
            if (time < count) {
                distance += speed * time;
                time = 0;
            } else {
                distance += speed * count;
                time -= count;
            }
        }

        resting = !resting;
    }

    return distance;
}

int race(Raindeers raindeers, int time) {
    std::map<std::string, bool> resting;
    std::map<std::string, int> timing;

    std::vector<int> distances(raindeers.size());
    std::vector<int> points(raindeers.size());

    for (unsigned int i = 0; i < raindeers.size(); i++) {
        std::string raindeer = std::get<0>(raindeers[i]);
        resting[raindeer] = false;
        timing[raindeer] = std::get<2>(raindeers[i]);
    }

    for (int k = 0; k < time; k++) {
        for (unsigned int i = 0; i < raindeers.size(); i++) {
            Raindeer raindeer = raindeers[i];

            std::string name = std::get<0>(raindeer);
            int speed = std::get<1>(raindeer);
            int count = std::get<2>(raindeer);
            int rest = std::get<3>(raindeer);

            bool isResting = resting[name];
            timing[name] -= 1;

            if (!isResting) distances[i] += speed;
            if (timing[name] == 0) {
                resting[name] = !isResting;
                if (resting[name]) timing[name] = rest;
                else timing[name] = count;
            }
        }

        int max = *std::max_element(distances.begin(), distances.end());
        for (unsigned int i = 0; i < raindeers.size(); i++)
            if (distances[i] == max) points[i] += 1;
    }

    int max = *std::max_element(points.begin(), points.end());
    return max;
}

int main(int, char**) {
    Raindeers raindeers = getRaindeers();

    // Part one
    std::vector<int> distances(raindeers.size());

    for (unsigned int i = 0; i < raindeers.size(); i++)
        distances[i] = calculateDistance(raindeers[i], 2503);

    int max = *std::max_element(distances.begin(), distances.end());
    printf("The winning raindeer goes %i kilometers.\n", max);

    // Part two
    int points = race(raindeers, 2503);
    printf("The winning raindeer has %i points.\n\n", points);
}

