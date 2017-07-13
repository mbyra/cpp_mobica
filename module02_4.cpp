#include <catch.hpp>
#include <iostream>

/*
 * Make the tests pass.
 * Please, do not modify the code outside the 'MODIFY MARKER' blocks.
 * You'll probably be able to see more than one solution that involves
 * modifying something outside those blocks. The point however, is to
 * learn something, so please obey this rule.
 */

TEST_CASE("virtual functions and object size", "[ex4]")
{
    std::cout << "=========================== some info about size ===============================\n";
    std::cout << "================================================================================\n";
    std::cout << "sizeof(int*):      " << sizeof(int*)
              << ", alignof(int*):      " << alignof(int*) << '\n';
    std::cout << "sizeof(void*):     " << sizeof(void*)
              << ", alignof(void*):     " << alignof(void*) << '\n';
    std::cout << "sizeof(void(*)()): " << sizeof(void(*)())
              << ", alignof(void(*)()): " << alignof(void(*)()) << " (make sure you know what this is...)\n";
    std::cout << "sizeof(int):       " << sizeof(int)
              << ", alignof(int):       " << alignof(int) << '\n';
    std::cout << "================================================================================\n";

    struct A
    {
        int x;
        int y;
        void f() {}
    };

    struct B
    {
        int x;
        int y;
        virtual void f() {};
    };

    struct C
    {
        int x;
        virtual void f() {};
    };

    struct D
    {
        int x;
        int y;
        int* z;
    };

    // also, when you make the test pass, make sure you understand why it passes :-)
    // MODIFY BLOCK BEGIN
    const int diff_A_B = 1003;
    const int diff_B_C = 1003;
    const int diff_B_D = 1003;
    // MODIFY BLOCK END

    REQUIRE(sizeof(A) == sizeof(B) + diff_A_B);
    REQUIRE(sizeof(B) == sizeof(C) + diff_B_C);
    REQUIRE(sizeof(B) == sizeof(D) + diff_B_D);
}
