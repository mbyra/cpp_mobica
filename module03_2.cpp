#include <catch.hpp>

#include <sstream>

// namespace "nonstd" contains an optional utility for making the operator>> more readable
// bonus point for figuring how to use it
namespace nonstd
{
struct skip
{
    const char* m_text;
    skip(const char* text) : m_text{text} {}
};

std::istream& operator>>(std::istream& input, const skip& s)
{
    std::ios_base::fmtflags f = input.flags();
    input >> std::noskipws;

    const char* text = s.m_text;
    char c;
    while (input && *text)
    {
        input >> c;
        if (c != *text)
        {
            input.setstate(std::ios::failbit);
        }
        ++text;
    }

    input.flags(f);
    return input;
}
}

// Actual exercise starts here

struct Point
{
    int x;
    int y;
};

bool operator==(const Point& lhs, const Point& rhs)
{
    return lhs.x == rhs.x && lhs.y == rhs.y;
}

// MODIFY BLOCK BEGIN
std::istream& operator>>(std::istream& in, Point& /*p*/)
{
    return in;
}
// MODIFY BLOCK END

TEST_CASE("deserialize using input operator", "[ex2]")
{
    std::stringstream input{"{x: 12, y: -14}"};
    Point p;
    input >> p;
    REQUIRE((p == Point{12, -14}));
}
