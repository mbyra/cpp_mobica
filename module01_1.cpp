#include <catch.hpp>
#include "utilities.hpp"

/*
 * Make the tests pass.
 * Please, do not modify the code outside the 'MODIFY MARKER' blocks.
 * You'll probably be able to see more than one solution that involves
 * modifying something outside those blocks. The point however, is to
 * learn something, so please obey this rule.
 */

TEST_CASE("choose the right capture", "[ex1]")
{
    const int value = getRandomInt();
    int copyOfValue{value};

    SECTION("should modify a value")
    {
        // MODIFY MARKER BEGIN
        auto foo = [](){ };
        // MODIFY MARKER END
        foo();
        REQUIRE(value + 13 == copyOfValue);
    }

    SECTION("should remember a value but not modify the original")
    {
        // MODIFY MARKER BEGIN
        auto bar = [](){ return 0; };
        // MODIFY MARKER END

        const int old_value = value;

        // erasing value
        int& evil = const_cast<int&>(value);
        evil = getRandomInt();
        copyOfValue = evil;

        // lambda should retain information about old value
        int rv = bar();
        REQUIRE(rv == old_value + 5);
        REQUIRE(value == copyOfValue);
    }
}
