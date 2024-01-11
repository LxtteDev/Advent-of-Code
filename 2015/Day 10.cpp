// Advent of Code - 2015 - Day 10

#include <stdio.h>
#include <fstream>
#include <string>

std::string input = "1113222113";

std::string lookAndSay(std::string string) {
    int length = 0;
    std::string current = "";
    std::string output = "";

    for (unsigned int i = 0; i < string.length(); i++) {
        std::string character = string.substr(i, 1);

        if (character != current) {
            if (current.length() > 0) output += std::to_string(length) + current;

            current = character;
            length = 1;
        } else
            length++;
    }

    if (current.length() > 0) output += std::to_string(length) + current;

    return output;
}

int main(int, char**) {
    // Part one
    for (unsigned int i = 0; i < 40; i++)
        input = lookAndSay(input);

    printf("The first sequence has a length of %zu characters.\n", input.length());

    // Part Two
    for (unsigned int i = 0; i < 10; i++)
        input = lookAndSay(input);

    printf("The final sequence has a length of %zu characters.\n\n", input.length());
}

