#include <catch.hpp>
#include <vector>
#include <algorithm>
#include <string>

/*
 * Make the tests pass.
 * Please, do not modify the code outside the 'MODIFY MARKER' blocks.
 * You'll probably be able to see more than one solution that involves
 * modifying something outside those blocks. The point however, is to
 * learn something, so please obey this rule.
 */

TEST_CASE("functors as predicates", "[ex2]")
{
    const std::vector<std::string> names = {"Bob", "Andrew", "Bill", "Zack", "James", "John", "Barney"};
    SECTION("should filter names starting with B")
    {
        const std::vector<std::string> expected_output = {"Bob", "Bill", "Barney"};
        std::vector<std::string> output = {};

        // MODIFY MARKER BEGIN
        const auto startsWithB = [](const std::string& /*s*/)
        {
            return false;
        };
        // MODIFY MARKER END

        std::copy_if(names.begin(), names.end(), std::back_inserter(output),
                     startsWithB);
        REQUIRE(output == expected_output);
    }
}

TEST_CASE("functors as transformation rules in algorithms", "[ex2]")
{
    const std::vector<int> input = {1, 2, 3, 4, 5, 6, 7, 8};

    SECTION("should apply stateless transformation to input")
    {
        const std::vector<int> expected_output = {1, 4, 9, 16, 25, 36, 49, 64};
        std::vector<int> output = {};

        // MODIFY MARKER BEGIN
        auto transformation = [](int /*value*/)
        {
            return 0;
        };
        // MODIFY MARKER END

        std::transform(input.begin(), input.end(), std::back_inserter(output),
                       transformation);
        REQUIRE(output == expected_output);

    }

    SECTION("should apply stateful transformation to input")
    {
        const std::vector<int> expected_output = {1, 3, 6, 10, 15, 21, 28, 36};
        std::vector<int> output = {};
        // MODIFY MARKER BEGIN
        auto transformation = [](int /*value*/)
        {
            return 0;
        };
        // MODIFY MARKER END

        std::transform(input.begin(), input.end(),
                       std::back_inserter(output), transformation);
        REQUIRE(expected_output == output);
    }
}
