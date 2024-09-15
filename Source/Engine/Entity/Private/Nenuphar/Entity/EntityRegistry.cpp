#include "Nenuphar/Entity/EntityRegistry.hpp"
#include "Nenuphar/Entity/Entity.hpp"


namespace Nenuphar
{

    Entity EntityRegistry::Create(std::string_view name)
    {
        auto entity = Container<Entity>::MaxTIndex;

        if (m_entities.size() == 0)
        {
            NCHECK(m_maxEntityID < MAX_ENTITIES);
            entity = m_maxEntityID++;
        }
        else
        {
            entity = m_entities.back();
            m_entities.pop_back();
        }

        m_entityMasks.Add(entity, {});

        if (!name.empty())
        {
            m_entityNames[entity] = name;
        }

        return entity;
    }

    std::string EntityRegistry::GetEntityName(Entity entity)
    {
        NCHECK(m_entityMasks.Get(entity) && entity > 0)

        return m_entityNames[entity];
    }

    void EntityRegistry::Remove(Entity entity)
    {
        NCHECK(m_entityMasks.Get(entity) && entity > 0)

        std::string name = GetEntityName(entity);
        ComponentMask& mask = GetEntityMask(entity);

        RemoveFromGroup(mask, entity);

        for (int i = 0; i < MAX_COMPONENTS; i++)
        {
            if (mask[i] == 1)
            {
                m_componentPools[i]->Remove(entity);
            }
        }

        m_entityMasks.Remove(entity);
        m_entityNames.erase(entity);
        m_entities.push_back(entity);

        entity = NULL_ENTITY;
    }

    void EntityRegistry::RemoveFromGroup(ComponentMask& mask, Entity entity)
    {
        if (mask.none())
        {
            return;
        }

        EntitySparseSet<Entity>& group = GetGroupedEntities(mask);
        group.Remove(entity);

        // Delete grouping if it's empty
        if (group.IsEmpty())
        {
            m_groupings.erase(mask);
        }
    }

    EntityRegistry::ComponentMask& EntityRegistry::GetEntityMask(Entity entity)
    {
        ComponentMask* mask = m_entityMasks.Get(entity);
        NCHECK(mask);
        return *mask;
    }

    void EntityRegistry::AssignToGroup(ComponentMask& mask, Entity entity)
    {
        // If mask is empty, no group
        if (mask.none())
        {
            return;
        }

        m_groupings.emplace(std::piecewise_construct,
                            std::forward_as_tuple(mask),
                            std::forward_as_tuple());

        m_groupings[mask].Add(entity, std::move(entity));
    }

    EntitySparseSet<Entity>& EntityRegistry::GetGroupedEntities(ComponentMask& mask)
    {
        auto found = m_groupings.find(mask);
        NCHECK(found != m_groupings.end());
        return found->second;
    }


}// namespace Nenuphar
