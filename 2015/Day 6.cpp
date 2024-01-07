// Advent of Code - 2015 - Day 6

#include <stdio.h>
#include <fstream>
#include <string>
#include <vector>
#include <tuple>
#include <regex>

enum Action {
    TurnOff = 9,
    TurnOn = 8,
    Toggle = 7
};

typedef std::tuple<int, int> Light;
typedef std::tuple<bool, int> GridLight;
typedef std::tuple<Action, Light, Light> ActionGroup;
typedef std::vector<std::vector<GridLight>> LightsArray;

std::regex turnOnRegex("turn on");
std::regex turnOffRegex("turn off");

// Parse Data
std::vector<ActionGroup> getActions() {
    std::vector<ActionGroup> actions;
    std::ifstream actionsFile("2015/Day 6.txt");

    std::string line;
    while (std::getline( actionsFile, line )) {
        int start = 0;

        if (std::regex_search( line, turnOnRegex ))
            start = 8;
        else if (std::regex_search( line, turnOffRegex ))
            start = 9;
        else
            start = 7;

        line = line.substr(start);
        int seperator = line.find("through");

        std::string startString = line.substr(0, seperator - 1);
        std::string endString = line.substr(seperator + 8);

        int startSeperator = startString.find(",");
        int endSeperator = endString.find(",");

        Light startLight = std::make_tuple( std::stoi(startString.substr( 0, startSeperator )), std::stoi(startString.substr(startSeperator + 1)) );
        Light endLight = std::make_tuple( std::stoi(endString.substr( 0, endSeperator )), std::stoi(endString.substr(endSeperator + 1)) );

        ActionGroup group = std::make_tuple( static_cast<Action>(start), startLight, endLight );
        actions.push_back(group);
    }

    return actions;
}

LightsArray generateGrid() {
    LightsArray lightsArray(1000);
    for (unsigned int i = 0; i < lightsArray.size(); i++)
        lightsArray[i].resize(1000);

    return lightsArray;
}

int countGrid(LightsArray& array) {\
    int count = 0;

    for (unsigned int x = 0; x < array.size(); x++)
        for (unsigned int y = 0; y < array[x].size(); y++)
            if (std::get<0>( array[x][y] )) count++;

    return count;
}

int countBrightness(LightsArray& array) {\
    int brightness = 0;

    for (unsigned int x = 0; x < array.size(); x++)
        for (unsigned int y = 0; y < array[x].size(); y++)
            brightness += std::get<1>( array[x][y] );

    return brightness;
}


void turnOnGrid(LightsArray& array, Light start, Light end) {
    for (int x = std::get<0>(start); x < (std::get<0>(end) + 1); x++)
        for (int y = std::get<1>(start); y < (std::get<1>(end) + 1); y++)
            array[x][y] = std::make_tuple( true, std::get<1>( array[x][y] ) + 1 );
}

void turnOffGrid(LightsArray& array, Light start, Light end) {
    for (int x = std::get<0>(start); x < (std::get<0>(end) + 1); x++)
        for (int y = std::get<1>(start); y < (std::get<1>(end) + 1); y++)
            array[x][y] = std::make_tuple( false, std::max( std::get<1>( array[x][y] ) - 1, 0 ) );
}

void toggleGrid(LightsArray& array, Light start, Light end) {
    for (int x = std::get<0>(start); x < (std::get<0>(end) + 1); x++)
        for (int y = std::get<1>(start); y < (std::get<1>(end) + 1); y++)
            array[x][y] = std::make_tuple( !(std::get<0>( array[x][y] )), std::get<1>( array[x][y] ) + 2 );
}


int main(int, char**) {
    std::vector<ActionGroup> actions = getActions();
    LightsArray lightsArray = generateGrid();

    for (unsigned int i = 0; i < actions.size(); i++) {
        ActionGroup& group = actions[i];

        Action action = std::get<0>(group);
        Light start = std::get<1>(group);
        Light end = std::get<2>(group);

        if (action == Action::TurnOn) turnOnGrid(lightsArray, start, end);
        else if (action == Action::TurnOff) turnOffGrid(lightsArray, start, end);
        else if (action == Action::Toggle) toggleGrid(lightsArray, start, end);
    }

    // Part One
    int lights = countGrid(lightsArray);
    printf("There are %i lights lit in the array.\n", lights);

    // Part Two
    int brightness = countBrightness(lightsArray);
    printf("The total brightness of the array is %i units.\n\n", brightness);
}

