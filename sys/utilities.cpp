#include "utilities.hpp"

#include <random>
#include <algorithm>

int getRandomInt(int a, int b)
{
    static std::mt19937 generator(std::random_device{}());
    std::uniform_int_distribution<> distr(a, b);
    return distr(generator);
}

std::string getRandomString(std::string::size_type size)
{
    std::string rv;
    rv.reserve(size);

    const auto randomChar = []
    {
        static const char lookupTbl[] =
        "0123456789"
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "abcdefghijklmnopqrstuvwxyz";
        static const int maxIndex = sizeof(lookupTbl) - 2; // skip over the implicit '\0' at the end of char[]

        return lookupTbl[getRandomInt(0, maxIndex)];
    };

    std::generate_n(std::back_inserter(rv), size, randomChar);

    return rv;
}
