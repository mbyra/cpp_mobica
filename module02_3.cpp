#include <catch.hpp>
#include <string>
#include <sstream>
#include <typeinfo>
#include <typeindex>
#include <memory>

/*
 * Make the tests pass.
 * Please, do not modify the code outside the 'MODIFY MARKER' blocks.
 * You'll probably be able to see more than one solution that involves
 * modifying something outside those blocks. The point however, is to
 * learn something, so please obey this rule.
 */

namespace ex3
{

class Animal
{
public:
    virtual ~Animal() = default; // comment out this line and analyze the compiler warning
    virtual std::string speciesName() = 0;
    virtual std::string individualName() = 0;
};

std::string aLittleStory(Animal* a1, Animal* a2)
{
    std::unique_ptr<Animal> p1{a1};
    std::unique_ptr<Animal> p2{a2};

    if (a1 != nullptr and a2 != nullptr)
    {
        std::stringstream story;
        story << "A nasty " << a1->speciesName() << " named " << a1->individualName()
              << " likes to chase a poor little " << a2->speciesName()
              << " named " << a2->individualName() << ".";


        const std::type_info& type_a1 = typeid(*a1);
        const std::type_info& type_a2 = typeid(*a2);

        // checking if we have proper polymorphic behavior i.e. a1 and a2 are of different type
        if (std::type_index(type_a1) != std::type_index(type_a2))
        {
            return story.str();
        }
        else
        {
            return "use different types for a1 and a2";
        }
    }
    else
    {
        return "";
    }
}

}

TEST_CASE("proper polymorphic behavior", "[ex3]")
{
    ex3::Animal* first = nullptr;
    ex3::Animal* second = nullptr;
    // MODIFY BLOCK BEGIN

    // define classes here, create instances of those classes on the heap,
    // assign them to the pointers defined above

    // MODIFY BLOCK END

    REQUIRE(ex3::aLittleStory(first, second) ==
            "A nasty dog named Buster likes to chase a poor little cat named Peanut.");
}
