#include <catch.hpp>
#include <string>
#include <sstream>

struct Location
{
    std::string name;
    int x;
    int y;
    double height;
};

// MODIFY BLOCK BEGIN
std::ostream& operator<<(std::ostream& out, const Location& /*l*/)
{
    return out;
}
// MODIFY BLOCK END

TEST_CASE("serialize objects to string", "[ex1]")
{
    std::stringstream s;
    Location inn{"Prancing Pony", 10, -53, 1234.56};
    Location river{"Anduin", 1001, 5467, 256.1};

    s << inn;

    CHECK(s.str() == "{name: \"Prancing Pony\", x: 10, y: -53, height: 1.2346e+03}");

    s << "\n" << river;

    REQUIRE(s.str() ==
            "{name: \"Prancing Pony\", x: 10, y: -53, height: 1.2346e+03}\n"
            "{name: \"Anduin\", x: 1001, y: 5467, height: 2.5610e+02}");
}
