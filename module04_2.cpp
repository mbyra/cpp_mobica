#include <catch.hpp>

#include <stdexcept>
#include <cstring>
#include <string>

void mayThrow(int behaviorRegulator)
{
    switch (behaviorRegulator)
    {
    case 1:
        throw std::runtime_error{"1"};

    default:
        return;
    }
}

void magicCStringOperation(const char* str, char* output)
{
    const int strSize = std::strlen(str);
    for (int i = 0; i < strSize; ++i)
    {
        output[i] = str[strSize - i - 1];
    }
    output[strSize] = '\0';
}

std::string wrapperForMagicCStringOperation(const std::string& str, int behaviorRegulator)
{
    const int size = str.size();
    // MODIFY BLOCK BEGIN
    char* buffer = new char[size + 1]; // we need one additional element for the null terminator
    // MODIFY BLOCK END

    magicCStringOperation(str.c_str(), buffer);

    mayThrow(behaviorRegulator);

    std::string result{buffer};
    // MODIFY BLOCK BEGIN
    delete[] buffer;
    // MODIFY BLOCK END

    return result;
}

TEST_CASE("using smart pointers", "[ex2]")
{
    std::string input{"abcdefg"};

    SECTION("should work when no exception is thrown")
    {
        std::string res = wrapperForMagicCStringOperation(input, 0);
        REQUIRE(res == "gfedcba");
    }

    SECTION("should not leak memory when exception is thrown")
    {
        REQUIRE_THROWS(wrapperForMagicCStringOperation(input, 1));
    }
}
