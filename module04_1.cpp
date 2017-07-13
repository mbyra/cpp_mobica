#include <catch.hpp>
#include <memory>
#include <stdexcept>

namespace ex1
{
// This class is an abstract representation of a resource a program may use.
// Key operations for a resource are the acquire/release pair of functions.
// Properly accessing a resource should always be preceded by acquiring the resource
// and releasing it after it has been used.
// Examples of resources are
// - memory - in this case acquire/release map to new/delete
// - file - in this case acquire/release map to open/close
// - mutex - in this case acquire/release map to lock/unlock
class Resource
{
public:
    virtual ~Resource() = default;
    virtual void acquire() = 0;
    virtual void release() = 0;

    virtual void access() = 0;
};

// MODIFY BLOCK BEGIN
class ResourceGuard
{
public:
    ResourceGuard(std::unique_ptr<Resource> resource)
        : m_resource{std::move(resource)}
    {
    }

    Resource* operator->() { return m_resource.get(); }
    Resource& operator*() { return *m_resource; }
private:
    std::unique_ptr<Resource> m_resource;
};
// MODIFY BLOCK END

class MockResource : public Resource
{
public:
    MockResource(int& ac)
        : acquisitionCount{ac}
    {}

    void acquire() { ++acquisitionCount; }
    void release() { --acquisitionCount; }

    void access()
    {
        if (acquisitionCount < 1) { throw std::runtime_error("bad access"); }
    }

private:
    int& acquisitionCount;
};

TEST_CASE("implementing RAII", "[ex1]")
{
    int acquisitionCount{0};

    {
        ResourceGuard guardedResource{std::make_unique<MockResource>(acquisitionCount)};

        REQUIRE_NOTHROW(
            guardedResource->access()
            );

        REQUIRE_NOTHROW(
            (*guardedResource).access()
            );
    }

    REQUIRE(acquisitionCount == 0);
}

}
