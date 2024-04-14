#include "Nenuphar/Entity/Entity.hpp"

namespace Nenuphar
{

    Entity EntityRegistry::LastEntity = 0;
    Entity EntityRegistry::LastArchetype = 0;

    Entity EntityRegistry::Create()
    {
        Entity entity = LastEntity++;
        m_entities.push_back(entity);
        m_entityArchetypes[entity] = { 0, { } };
        return entity;
    }

    void EntityRegistry::Remove(Entity entity)
    {
        auto entityIterator = std::find(m_entities.begin(), m_entities.end(), entity);
        if (entityIterator != m_entities.cend())
        {
            m_entities.erase(entityIterator);
            m_entityArchetypes.erase(entity);
        }
    }

    EntityRegistry::EntityRegistry()
    {
        auto a = Archetype({ });
        m_archetypes.insert(a);
    }


}
