
#include <catch2/catch_test_macros.hpp>

#include "Nenuphar/Entity/EntityRegistry.hpp"

using namespace Nenuphar;

struct AComponent 
{
    int x;
};

struct BComponent 
{
    int x;
};

TEST_CASE("Check creating entity.", "[Registry::Create]")
{
    EntityRegistry registry;
    REQUIRE(registry.Create() == 0);
    REQUIRE(registry.Create() == 1);
}

TEST_CASE("Add a component to an entity", "[Registry::AddComponent]")
{
    EntityRegistry registry;
    Entity entity = registry.Create();

    REQUIRE_FALSE(registry.HasComponent<AComponent>(entity));

    REQUIRE_NOTHROW(registry.AddComponent<AComponent>(entity, AComponent(0)));

    REQUIRE(registry.HasComponent<AComponent>(entity));
}

TEST_CASE("Get and modify multiple component to an entity", "[Registry::GetComponent]")
{

    EntityRegistry registry;
    Entity entity = registry.Create();

    REQUIRE_NOTHROW(registry.AddComponent<AComponent>(entity, AComponent(5)));

    auto& component = registry.GetComponent<AComponent>(entity);
    REQUIRE(component.x == 5);

    component.x = 8;
    component = registry.GetComponent<AComponent>(entity);
    REQUIRE(component.x == 8);

    REQUIRE_NOTHROW(registry.AddComponent<BComponent>(entity, BComponent(2)));

    auto& componentB1 = registry.GetComponent<BComponent>(entity);
    REQUIRE(componentB1.x == 2);

    REQUIRE(registry.HasComponent<AComponent>(entity));

    component = registry.GetComponent<AComponent>(entity);
    REQUIRE(component.x == 8);
}

