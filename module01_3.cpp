#include <catch.hpp>
#include <functional>
#include "utilities.hpp"

/*
 * Make the tests pass.
 * Please, do not modify the code outside the 'MODIFY MARKER' blocks.
 * You'll probably be able to see more than one solution that involves
 * modifying something outside those blocks. The point however, is to
 * learn something, so please obey this rule.
 */

namespace ex3
{

using CommLink = std::function<void(int)>;

class Sender
{
public:
    Sender(CommLink link, int secret) : m_link{link}, m_secret{secret} {}
    void sendSecretViaCommLink() const { m_link(m_secret); }

private:
    CommLink m_link;
    int m_secret;
};

class Receiver
{
public:
    CommLink getCommLink()
    {
        // MODIFY MARKER BEGIN
        return [](int /*secret*/){};
        // MODIFY MARKER END
    }
    int revealSecret() { return m_notSoSecretNumber; }

private:
    int m_notSoSecretNumber{-1};
};

}
TEST_CASE("Alice and Bob" , "[ex3]")
{
    const int verySecretNumber = getRandomInt();
    ex3::Receiver Bob;
    const ex3::Sender Alice{Bob.getCommLink(), verySecretNumber};

    SECTION("Alice should be able to share a secret with Bob")
    {
        Alice.sendSecretViaCommLink();

        REQUIRE(Bob.revealSecret() == verySecretNumber);
    }
}
