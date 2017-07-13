#include <catch.hpp>

#include <vector>
#include <utility>
#include <string>
#include <sstream>

struct TOCEntry
{
    std::string chapterName;
    int chapterStartPage;
    int pageWidth;
};

// MODIFY BLOCK BEGIN
std::ostream& operator<<(std::ostream& out, const TOCEntry& /*e*/)
{
    return out;
}
// MODIFY BLOCK END

void printTableOfContent(std::ostream& out, const std::vector<TOCEntry>& data)
{
    for (const auto& entry : data)
    {
        out << entry << '\n';
    }
}

TEST_CASE("use width and fill manipulators correctly", "[ex3]")
{
    std::string expected =
        "ch01.......___5\n"
        "ch002.......__16\n"
        "ch0003......._123\n";

    std::stringstream result;

    //saving stream state
    const auto formatFlags = result.flags();
    const char fillChar = result.fill();

    printTableOfContent(result, {{"ch01",     5, 11},
                                 {"ch002",   16, 12},
                                 {"ch0003", 123, 13}});

    REQUIRE(result.str() == expected);

    // make sure the stream state is restored
    REQUIRE(formatFlags == result.flags());
    REQUIRE(fillChar == result.fill());
}
