// Advent of Code - 2015 - Day 2

#include <algorithm>
#include <fstream>
#include <stdio.h>
#include <vector>
#include <string>
#include <tuple>

// Parse Data
std::vector<std::tuple<int, int, int>> getPresents() {
    std::vector<std::tuple<int, int, int>> presents;
    std::ifstream presentsFile("2015/Day 2.txt");
    std::string deli = "x";

    std::string line;
    while (std::getline(presentsFile, line)) {
        std::vector<int> presentVec(3);

        for (int i = 0; i < 3; i++) {
            std::string token = line.substr(0, line.find(deli));
            line.erase(0, line.find(deli) + 1);
            presentVec[i] = std::stoi(token);
        }

        std::tuple<int, int, int> present = { presentVec[0], presentVec[1], presentVec[2] };
        presents.push_back(present);
    }

    return presents;
}

// Get Paper
int requiredPaper(int l, int w, int h) {
    int lw = l * w;
    int lh = l * h;
    int wh = w * h;

    return 2 * lw + 2 * lh + 2 * wh + std::min(lw, std::min(lh, wh));
}


// Get Ribbon
int requireRibbon(int l, int w, int h) {
    std::vector<int> dim = { l, w, h };
    std::sort(dim.begin(), dim.begin() + 3);

    return 2 * dim[0] + 2 * dim[1] + l * w * h;
}

int main(int, char**) {
    std::vector<std::tuple<int, int, int>> presents = getPresents();
    int totalPaper = 0;
    int totalRibbon = 0;

    for (unsigned int i = 0; i < presents.size(); i++) {
        std::tuple<int, int, int> present = presents[i];
        int paper = requiredPaper(std::get<0>(present), std::get<1>(present), std::get<2>(present));
        int ribbon = requireRibbon(std::get<0>(present), std::get<1>(present), std::get<2>(present));

        totalPaper += paper;
        totalRibbon += ribbon;
    }

    printf("%i sq. ft. of warping paper is required.\n", totalPaper);
    printf("%i ft. of warping ribbon is also required.\n\n", totalRibbon);
}

