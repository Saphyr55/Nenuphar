#include "Nenuphar/Entity/Entity.hpp"

namespace Nenuphar
{

    Entity EntityRegistry::Create()
    {
        Entity entity = m_entities.size();
        m_entities.push_back(entity);

        m_entityArchetypes[entity] = 0;

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


}
