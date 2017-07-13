#include <catch.hpp>
#include <trompeloeil.hpp>
#include <utilities.hpp>

#include <memory>
#include <vector>

using Value = int;

class Observer
{
public:
    virtual ~Observer() = default;
    virtual void notify(Value) = 0;
};

class Observable
{
public:
    virtual ~Observable() = default;
    virtual void addObserver(std::shared_ptr<Observer>) = 0;
    virtual void setValue(Value) = 0;
    virtual const Value& getValue() const = 0;
};

class MockObserver : public Observer
{
public:
    MAKE_MOCK1(notify, void(Value), override);
};

// MODIFY BLOCK BEGIN
class ObservableImpl : public Observable
{
public:
    ObservableImpl(Value initialValue)
        : v{initialValue}
    {}

    void addObserver(std::shared_ptr<Observer>) override {}
    void setValue(Value) override {}
    const Value& getValue() const override { return v; }

private:
    Value v;
};
// MODIFY BLOCK END

TEST_CASE("adding observers", "[ex3]")
{
    using trompeloeil::eq;
    const Value initialValue{};
    const Value newValue{42};

    int callCount = 0;

    ObservableImpl subject{initialValue};
    auto observerPtr = std::make_shared<MockObserver>();

    {
        REQUIRE_CALL(*observerPtr, notify(eq(initialValue)));

        subject.addObserver(observerPtr);
    }

    SECTION("when value is changed, observer is updated")
    {
        REQUIRE_CALL(*observerPtr, notify(eq(newValue)));

        subject.setValue(newValue);

        SECTION("when another observer is added, it gets notification for new value")
        {
            auto secondObserverPtr = std::make_shared<MockObserver>();
            REQUIRE_CALL(*secondObserverPtr, notify(eq(newValue)));

            subject.addObserver(secondObserverPtr);
        }
    }

    SECTION("when observer is added a second time, it does not get initial notification")
    {
        // notify should not be called, so no additional requirement setup needed
        subject.addObserver(observerPtr);

        SECTION("when value changes, observer gets notified only once")
        {
            REQUIRE_CALL(*observerPtr, notify(eq(newValue)));

            subject.setValue(newValue);
        }
    }

    SECTION("when observer is destroyed, Observable should not extend it's lifetime")
    {
        using trompeloeil::deathwatched;
        auto secondObserverPtr = std::make_shared<deathwatched<MockObserver>>();

        REQUIRE_CALL(*secondObserverPtr, notify(eq(initialValue)));
        subject.addObserver(secondObserverPtr);

        REQUIRE_DESTRUCTION(*secondObserverPtr);
        secondObserverPtr.reset();

        SECTION("when observer has been destroyed, Observable should not experience runtime crash")
        {
            REQUIRE_CALL(*observerPtr, notify(eq(newValue)));

            subject.setValue(newValue);
        }

    }

    // SECTION("observable can accommodate arbitrary number of observers")
    // {
    //     const int numOfObservers = getRandomInt();
    //     std::vector<std::shared_ptr<MockObserver>> observers;
    //     std::vector<std::unique_ptr<trompeloeil::expectation>> delayedExpectations;
    //     observers.reserve(numOfObservers);

    //     for (int i = 0; i < numOfObservers; ++i)
    //     {
    //         observers.emplace_back(std::make_shared<MockObserver>());
    //         REQUIRE_CALL(*observers.back(), notify(eq(initialValue)));
    //         delayedExpectations.emplace_back(
    //             NAMED_REQUIRE_CALL(*observers.back(), notify(eq(newValue))));
    //         subject.addObserver(observers.back());
    //     }

    //     REQUIRE_CALL(*observerPtr, notify(eq(newValue)));

    //     subject.setValue(newValue);
    // }
}
