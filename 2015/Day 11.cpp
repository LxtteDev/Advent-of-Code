// Advent of Code - 2015 - Day 11

#include <iostream>
#include <stdio.h>
#include <string>

std::string input = "hepxcrrq";

std::string increment(std::string string) {
    bool inc = false;

    if (string == "zzzzzzzz") throw std::runtime_error("Reached max string");

    int max = -1;
    for (unsigned int i = 0; i < string.size(); i++) {
        if (string[i] == 'z') {
            max = i;
        } else {
            break;
        }
    }

    for (int i = 7; i > max; i--) {
        int ascii = int(string[i]);
        inc = false;

        if (string[i] == 'z') {
            inc = true;
            ascii = 96;
        }

        string[i] = char(ascii + 1);
        if (!inc) break;
    }
    
    return string;
}

bool verifyPassword(std::string password) {
    int length = 0;
    int currentChar = 0;

    int pairOne = 0;
    int pairOneLength = 0;
    
    int pairTwo = 0;
    int pairTwoLength = 0;

    for (unsigned int i = 0; i < password.size(); i++) {
        int ascii = int(password[i]);
     
        if (ascii == 105 || ascii == 111 || ascii == 108) return false; // i o l

        if (length < 3) {
            if (ascii == currentChar + 1) length++;
            else length = 1;

            currentChar = ascii;
        }

        if (pairOneLength < 2) {
            if (pairOne != ascii) pairOneLength = 1;
            else pairOneLength++;

            pairOne = ascii;
        }

        if (pairTwoLength < 2 && ascii != pairOne) {
            if (pairTwo != ascii) pairTwoLength = 1;
            else pairTwoLength++;

            pairTwo = ascii;
        }
    }

    if (length < 3 || pairOneLength < 2 || pairTwoLength < 2) return false;
    return true;
}

int main(int, char**) {
    // Part one
    std::string password = input;
    int i = 0;

    while (true) {
        password = increment(password);
        bool valid = verifyPassword(password);
        i++;

        if (valid) break;
    }

    printf("Found a valid password %s after %i iterations.\n", password.c_str(), i);

    // Part two
    i = 0;

    while (true) {
        password = increment(password);
        bool valid = verifyPassword(password);
        i++;

        if (valid) break;
    }

    printf("Found a new valid password %s after another %i iterations.\n\n", password.c_str(), i);
}

