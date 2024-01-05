// Advent of Code - 2015 - Day 4

#include <openssl/md5.h>
#include <stdio.h>
#include <iomanip>
#include <fstream>
#include <string>

std::string input = "ckczppom";

std::string md5(const std::string& input) {
    MD5_CTX context;
    MD5_Init(&context);
    MD5_Update(&context, input.c_str(), input.size());

    unsigned char digest[MD5_DIGEST_LENGTH];
    MD5_Final(digest, &context);

    std::stringstream ss;
    for (int i = 0; i < MD5_DIGEST_LENGTH; ++i)
        ss << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(digest[i]);

    return ss.str();
}

int main(int, char**) {
    // Part One
    int extraOne = 0;

    while (true) {
        std::string hash = md5(input + std::to_string(extraOne));
        if (hash.substr(0, 5) == "00000")
            break;
        extraOne++;
    }

    printf("%s%i = %s (%i)\n", input.c_str(), extraOne, md5(input + std::to_string(extraOne)).c_str(), extraOne);

    // Part Two
    int extraTwo = 0;

    while (true) {
        std::string hash = md5(input + std::to_string(extraTwo));
        if (hash.substr(0, 6) == "000000")
            break;
        extraTwo++;
    }

    printf("%s%i = %s (%i)\n\n", input.c_str(), extraTwo, md5(input + std::to_string(extraTwo)).c_str(), extraTwo);
}

