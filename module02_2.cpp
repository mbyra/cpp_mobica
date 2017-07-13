#include <catch.hpp>
#include <iostream>

/*
 * Make the tests pass.
 * Please, do not modify the code outside the 'MODIFY MARKER' blocks.
 * You'll probably be able to see more than one solution that involves
 * modifying something outside those blocks. The point however, is to
 * learn something, so please obey this rule.
 */

namespace ex2
{
class Base;
class Derived;
}

namespace {
class Counters
{
    int b_counter = 0;
    int d_counter = 0;
    friend class ex2::Base;
    friend class ex2::Derived;

public:
    int get_b_counter() { return b_counter; }
    int get_d_counter() { return d_counter; }
} c;
}

namespace ex2
{
// MODIFY BLOCK BEGIN
class Base
{
public:
    Base() { ++c.b_counter; }
    ~Base() { --c.b_counter; }
};

class Derived : public Base
{

public:
    Derived() { ++c.d_counter; }
    ~Derived() { --c.d_counter; }
};
// MODIFY BLOCK END
}

TEST_CASE("make sure all the destructors are called", "[ex2]")
{
    ex2::Base* d = new ex2::Derived{};
    REQUIRE(c.get_b_counter() == 1);
    REQUIRE(c.get_d_counter() == 1);
    delete d;
    REQUIRE(c.get_b_counter() == 0);
    REQUIRE(c.get_d_counter() == 0);
}
