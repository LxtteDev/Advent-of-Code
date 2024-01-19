// Advent of Code - 2015 - Day 18

#include <stdio.h>
#include <fstream>
#include <string>
#include <vector>

typedef std::vector<bool> Row;
typedef std::vector<Row> Grid;

// Parse Data
Grid generateGrid() {
    Grid grid;
    std::ifstream gridFile("2015/Day 18.txt");

    std::string line;
    while (std::getline( gridFile, line )) {
        Row row(100);
        for (unsigned int i = 0; i < line.length(); i++) row[i] = line[i] == '#';
        grid.push_back(row);
    }

    return grid;
}

void stepGrid(Grid& grid, bool part = false) {
    Grid original = grid;

    for (unsigned int i = 0; i < original.size(); i++) {
        for (unsigned int j = 0; j < original[i].size(); j++) {
            Row neighbours = {
                (i < 1 || j < 1)    ? false : original[i - 1][j - 1],
                (i < 1)             ? false : original[i - 1][j],
                (i < 1 || j > 98)   ? false : original[i - 1][j + 1],
                (j < 1)             ? false : original[i][j - 1],
                (j > 98)            ? false : original[i][j + 1],
                (i > 98 || j < 1)   ? false : original[i + 1][j - 1],
                (i > 98)            ? false : original[i + 1][j],
                (i > 98 || j > 98)  ? false : original[i + 1][j + 1]
            };

            int on = 0;
            for (unsigned int i = 0; i < 8; i++) if (neighbours[i]) on++;

            if (original[i][j]) grid[i][j] = on == 2 || on == 3;
            else grid[i][j] = on == 3;
        }
    }

    if (part) {
        grid[0][0]   = true;
        grid[0][99]  = true;
        grid[99][0]  = true;
        grid[99][99] = true;
    }
}

int main(int, char**) {
    Grid grid = generateGrid();

    // Part one
    for (unsigned int i = 0; i < 100; i++)
        stepGrid(grid);

    int total = 0;
    for (unsigned int i = 0; i < grid.size(); i++) for (unsigned int j = 0; j < grid[i].size(); j++)
            if (grid[i][j]) total++;

    printf("%i lights are on after the animation plays.\n", total);

    // Part two
    grid = generateGrid();
    grid[0][0]   = true;
    grid[0][99]  = true;
    grid[99][0]  = true;
    grid[99][99] = true;


    for (unsigned int i = 0; i < 100; i++)
        stepGrid(grid, true);

    total = 0;
    for (unsigned int i = 0; i < grid.size(); i++) for (unsigned int j = 0; j < grid[i].size(); j++)
            if (grid[i][j]) total++;

    printf("After realising the corners are stuck, %i lights are on after the animation plays\n\n", total);
}

