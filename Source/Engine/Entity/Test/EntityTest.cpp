
#include <catch2/catch_test_macros.hpp>

#include "Nenuphar/Entity/Entity.hpp"

using namespace Nenuphar;


TEST_CASE("Check creating entity.", "[Registry::Create]")
{
    EntityRegistry registry;
    REQUIRE(registry.Create() == 0);
    REQUIRE(registry.Create() == 1);
}

TEST_CASE("Add a component to an entity", "[Registry::AddComponent]")
{
    struct AComponent { };

    EntityRegistry registry;
    Entity entity = registry.Create();

    REQUIRE_FALSE(registry.HasComponent<AComponent>(entity));

    REQUIRE_NOTHROW(registry.AddComponent<AComponent>(entity, AComponent()));

    REQUIRE(registry.HasComponent<AComponent>(entity));
}

TEST_CASE("Get and modify a component to an entity", "[Registry::GetComponent]")
{
    struct AComponent
    {
        int x = 0;
    };

    struct BComponent
    {
        int x = 0;
    };

    EntityRegistry registry;
    Entity entity = registry.Create();

    REQUIRE_NOTHROW(registry.AddComponent<AComponent>(entity, AComponent(5)));

    auto& component = registry.GetComponent<AComponent>(entity);
    REQUIRE(component.x == 5);

    component.x = 8;
    auto& component2 = registry.GetComponent<AComponent>(entity);
    REQUIRE(component2.x == 8);

    REQUIRE_NOTHROW(registry.AddComponent<BComponent>(entity, BComponent(5)));

    auto& componentB1 = registry.GetComponent<BComponent>(entity);
    REQUIRE(componentB1.x == 5);

}