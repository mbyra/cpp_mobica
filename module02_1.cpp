#include <catch.hpp>
#include "utilities.hpp"

/*
 * Make the tests pass.
 * Please, do not modify the code outside the 'MODIFY MARKER' blocks.
 * You'll probably be able to see more than one solution that involves
 * modifying something outside those blocks. The point however, is to
 * learn something, so please obey this rule.
 */

namespace ex1
{

class Base
{
public:
    Base(int x) : m_x{x} {}
    Base() : Base{-7} {}

    int getX() { return m_x; }
private:
    int m_x;
};

class Derived : public Base
{
public:
    // MODIFY MARKER BEGIN
    Derived(int) {};
    // MODIFY MARKER END

    int getX() { return -3; };

    int bar()
    {
        // MODIFY MARKER BEGIN
        return getX();
        // MODIFY MARKER END
    }
};
}


TEST_CASE("initializing base", "[ex1]")
{
    const int randomInt = getRandomInt();
    ex1::Derived d{randomInt};

    REQUIRE(d.bar() == randomInt);
}
