// Advent of Code - 2015 - Day 9

#include <algorithm>
#include <stdio.h>
#include <fstream>
#include <string>
#include <limits>
#include <vector>
#include <regex>
#include <tuple>
#include <map>
#include <set>

typedef std::map<std::string, unsigned int> Route;
typedef std::map<std::string, Route> Routes;
typedef std::tuple<Routes, std::vector<std::string>> RoutesData;

std::regex routeRegex("([a-zA-Z]+) (?:to) ([a-zA-Z]+) (?:=) ([0-9]+)");

// Parse Data
RoutesData getRoutes() {
    Routes routes;
    std::vector<std::string> locations;
    std::set<std::string> locationsSet;
    std::ifstream routesFile("2015/Day 9.txt");

    std::string line;
    while (std::getline( routesFile, line )) {
        std::smatch matches;

        if (std::regex_search(line, matches, routeRegex)) {
            std::string start = matches[1].str();
            std::string end = matches[2].str();
            unsigned int distance = std::stoi(matches[3].str());

            if (locationsSet.insert(start).second) locations.push_back(start);
            if (locationsSet.insert(end).second) locations.push_back(end);

            if (routes.find(start) == routes.end()) routes[start] = {};

            routes[start][end] = distance;
        }
    }

    for (Routes::iterator i = routes.begin(); i != routes.end(); i++) {
        std::string iName = i->first;
        Route iRoutes = i->second;

        for (Route::iterator j = iRoutes.begin(); j != iRoutes.end(); j++) {
            std::string jName = j->first;
            unsigned int iDistance = j->second;

            if (routes.find(jName) == routes.end()) routes[jName] = {};
            if (routes[jName].find(iName) == routes[jName].end()) routes[jName][iName] = iDistance;
        }
    }

    std::sort(locations.begin(), locations.end());
    return std::make_tuple(routes, locations);
}

Route getLocationRoutes(Routes& routes, std::string location) {
    if (routes.find(location) == routes.end()) return {};
    return routes[location];
}

int main(int, char**) {
    RoutesData routesData = getRoutes();
    Routes routes = std::get<0>(routesData);
    std::vector<std::string> locations = std::get<1>(routesData);

 
    unsigned int shortest = std::numeric_limits<unsigned int>::max();
    unsigned int longest = 0;

    while (std::next_permutation(locations.begin(), locations.end())) {
        unsigned int pDistance = 0;
        bool valid = true;

        for (unsigned int i = 1; i < locations.size(); i++) {
            std::string start = locations[i - 1];
            std::string end = locations[i];

            if (routes.find(start) == routes.end()) { valid = false; break; };
            if (routes[start].find(end) == routes[start].end()) { valid = false; break; };

            pDistance += routes[start][end];
        }

        if (shortest > pDistance && valid) shortest = pDistance;
        if (longest < pDistance && valid) longest = pDistance;
    }

   // Part One
    printf("The shortest path that connects all cities is %u units.\n", shortest);

   // Part Two
    printf("The longest path that connects all cities is %u units.\n\n", longest);
}

