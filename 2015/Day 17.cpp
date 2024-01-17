// Advent of Code - 2015 - Day 17

#include <functional>
#include <algorithm>
#include <stdio.h>
#include <fstream>
#include <string>
#include <vector>
#include <limits>

typedef std::vector<int> Containers;

// Parse Data
Containers getContainers() {
    Containers containers;
    std::ifstream listFile("2015/Day 17.txt");

    std::string line;
    while (std::getline( listFile, line ))
        containers.push_back(std::stoi(line));

    return containers;
}

int countCombinations(Containers& containers, int max = 20, int total = 150, int index = 0, int used = 0) {
    if (total == 0) return 1;
    if (index == (int)containers.size() || total < 0 || used >= max) return 0;

    int include = countCombinations(containers, max, total - containers[index], index + 1, used + 1);
    int exclude = countCombinations(containers, max, total, index + 1, used);

    return include + exclude;
}

int minimumContainers(Containers& containers, int total = 150) {
    std::vector<int> sortedNumbers = containers;
    std::sort(sortedNumbers.rbegin(), sortedNumbers.rend());

    int minCount = std::numeric_limits<int>::max();

    std::function<void(int, int, int)> findMinCount = [&](int currentTarget, int currentIndex, int currentCount) {
        if (currentTarget == 0) { minCount = std::min(minCount, currentCount); return; }

        for (int i = currentIndex; i < (int)sortedNumbers.size(); i++)
            if (currentTarget - sortedNumbers[i] >= 0)
                findMinCount(currentTarget - sortedNumbers[i], i + 1, currentCount + 1);

        return void();
    };

    findMinCount(total, 0, 0);

    return (minCount == std::numeric_limits<int>::max()) ? -1 : minCount;
}

int main(int, char**) {
    Containers containers = getContainers();

    // Part one
    int total = countCombinations(containers);

    printf("Found %i combonations of containers that can hold the nog.\n", total);

    // Part two
    int maximum = minimumContainers(containers);
    total = countCombinations(containers, maximum);

    printf("Found %i combinations that use less than %i containers.\n\n", total, maximum);
}

