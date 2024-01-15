// Advent of Code - 2015 - Day 15

#include <stdio.h>
#include <fstream>
#include <string>
#include <vector>
#include <regex>
#include <tuple>

std::regex ingredientRegex("([a-zA-Z]+)[a-zA-Z\\:, ]+([-0-9]+)[a-zA-Z\\:, ]+([-0-9]+)[a-zA-Z\\:, ]+([-0-9]+)[a-zA-Z\\:, ]+([-0-9]+)[a-zA-Z\\:, ]+([-0-9]+)");

typedef std::tuple<std::string, int, int, int, int, int> Ingredient;
typedef std::vector<Ingredient> Ingredients;
typedef std::vector<int> Combination;

// Parse Data
Ingredients getIngredients() {
    Ingredients ingredients;
    std::ifstream listFile("2015/Day 15.txt");

    std::string line;
    while (std::getline( listFile, line )) {
        std::smatch matches;

        if (std::regex_search(line, matches, ingredientRegex)) {
            Ingredient ingredient = std::make_tuple(matches[1].str(), std::stoi(matches[2].str()), std::stoi(matches[3].str()), std::stoi(matches[4].str()), std::stoi(matches[5].str()), std::stoi(matches[6].str()));
            ingredients.push_back(ingredient);
        }
    }

    return ingredients;
}

std::tuple<int, int> bakeIngredients(Ingredients& ingredients) {
    int total = 100;

    int pScore = 0;
    int cScore = 0;

    for (int i = 0; i < total; i++) {
        for (int j = 0; j < total - i; j++) {
            for (int k = 0; k < total - i - j; k++) {
                int l = total - i - j - k;
                Combination combination = { i, j, k, l };

                int capacity = 0;
                int durability = 0;
                int flavour = 0;
                int texture = 0;
                int calories = 0;

                for (unsigned int j = 0; j < ingredients.size(); j++) {
                    Ingredient ingredient = ingredients[j];

                    capacity   += std::get<1>(ingredient) * combination[j];
                    durability += std::get<2>(ingredient) * combination[j];
                    flavour    += std::get<3>(ingredient) * combination[j];
                    texture    += std::get<4>(ingredient) * combination[j];
                    calories   += std::get<5>(ingredient) * combination[j];
                }

                int s = std::max(0, capacity) * std::max(0, durability) * std::max(0, flavour) * std::max(0, texture);

                if (s > pScore) pScore = s;
                if (calories == 500 && s > cScore) cScore = s;
            }
        }
    }

    return std::make_tuple(pScore, cScore);
}

int main(int, char**) {
    Ingredients ingredients = getIngredients();
    std::tuple<int, int> scores = bakeIngredients(ingredients);

    // Part one
    printf("The highest scoring cookie has a score of %i.\n", std::get<0>(scores));

    // Part two
    printf("The highest scoring cookie with 500 calories has a score of %i.\n\n", std::get<1>(scores));
}

