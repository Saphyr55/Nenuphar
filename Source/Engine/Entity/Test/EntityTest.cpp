
#include <catch2/catch_test_macros.hpp>

#include "Nenuphar/Entity/Entity.hpp"

using namespace Nenuphar;


TEST_CASE("Check creating entity.", "[Registry::Create]")
{
    EntityRegistry registry;
    REQUIRE(registry.Create() == 0);
    REQUIRE(registry.Create() == 1);
}

TEST_CASE("Add component to an entity", "[Registry::AddComponent]")
{

    struct AComponent { };

    EntityRegistry registry;
    Entity entity = registry.Create();

    REQUIRE_FALSE(registry.HasComponent<AComponent>(entity));

    REQUIRE_NOTHROW(registry.AddComponent(entity, AComponent()));

    REQUIRE(registry.HasComponent<AComponent>(entity));

}