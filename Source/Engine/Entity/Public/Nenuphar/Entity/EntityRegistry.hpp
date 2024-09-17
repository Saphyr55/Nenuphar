#pragma once

#include "ComponentTI.hpp"
#include "Nenuphar/Common/Container/SparseSet.hpp"
#include "Nenuphar/Common/Type/Type.hpp"
#include "Nenuphar/Core/Core.hpp"
#include "Nenuphar/Entity/ComponentTI.hpp"
#include "Nenuphar/Entity/Entity.hpp"
#include "Nenuphar/Entity/EntityBinding.hpp"
#include "Nenuphar/Entity/MemoryComponentSector.hpp"
#include "Nenuphar/Common/Instanciate.hpp"

#include <bitset>
#include <map>
#include <memory>
#include <unordered_set>


namespace Nenuphar
{

    template<typename TValue>
    using EntitySparseSet = SparseSet<Entity, TValue>;

    /**
     *
     */
    class EntityRegistry
    {

        static constexpr Entity NULL_ENTITY =
                std::numeric_limits<Entity>::max();

        static constexpr std::size_t MAX_ENTITIES = NULL_ENTITY - 1;

        static constexpr std::size_t MAX_COMPONENTS = 64;

        using ComponentMask = std::bitset<MAX_COMPONENTS>;

        using TName = const char*;

    public:
        /**
         *
         * @return
         */
        Entity Create(std::string_view name = "");

        /**
         *
         * @param entity
         */
        void Remove(Entity entity);

        /**
         *
         * @tparam C
         * @param entity
         * @param component
         */
        template<typename C>
        C& AddComponent(Entity entity, const C& component);

        /**
         *
         * @tparam C
         * @param entity
         * @param component
         */
        template<typename C>
        void RemoveComponent(Entity entity, const C& component);

        /**
         *
         * @tparam C
         * @param entity
         * @return
         */
        template<typename C>
        bool HasComponent(Entity entity);

        /**
        * @brief 
        * 
        * @param entity 
        * @return true 
        * @return false 
        */
        template<typename... C>
        bool HasComponents(Entity entity);

        /**
         *
         * @tparam C
         * @param entity
         * @return
         */
        template<typename C>
        C& GetComponent(Entity entity);

        /**
        * @brief 
        * 
        * @tparam C 
        * @return std::vector<std::tuple<Entity, C&...>> 
        */
        template<typename... C>
        std::vector<std::tuple<Entity, C&...>> View();


        /**
         * @brief Get the Entities that have the corresponding components.
         * 
         * @tparam C 
         * @return std::vector<Entity> 
         */
        template<typename... C>
        std::vector<Entity> GetEntities();


        /**
         * @brief Get the Entity Name.
         * 
         * @param entity 
         * @return std::string 
         */
        std::string GetEntityName(Entity entity);


    public:
        EntityRegistry() = default;
        EntityRegistry(const EntityRegistry&) = delete;
        EntityRegistry(EntityRegistry&&) = delete;
        ~EntityRegistry() = default;

    private:
        template<typename C>
        std::size_t GetComponentBitPosition();

        template<typename T>
        EntitySparseSet<T>& GetContainer(bool registerIfNotFound = false);

        template<typename Component>
        void SetComponentBit(ComponentMask& mask, bool val);

        template<typename Component>
        ComponentMask::reference GetComponentBit(ComponentMask& mask);

        ComponentMask& GetEntityMask(Entity entity);

        template<typename... Components>
        ComponentMask GetMask();

        void RemoveFromGroup(ComponentMask& mask, Entity entity);

        void AssignToGroup(ComponentMask& mask, Entity entity);

        EntitySparseSet<Entity>& GetGroupedEntities(ComponentMask& mask);

    private:
        std::vector<Entity> m_entities{};
        std::vector<UniquePtr<Container<Entity>>> m_componentPools{};

        SparseSet<Entity, ComponentMask> m_entityMasks{};
        std::unordered_map<ComponentMask, EntitySparseSet<Entity>> m_groupings{};
        std::unordered_map<Entity, std::string> m_entityNames{};
        std::unordered_map<TName, std::size_t> m_componentBitPosition{};

        Entity m_maxEntityID = 0;
    };

    template<typename C>
    C& EntityRegistry::GetComponent(Entity entity)
    {
        EntitySparseSet<C>& container = GetContainer<C>();

        C* component = container.Get(entity);
        NCHECK(component);

        return *component;
    }

    template<typename C>
    C& EntityRegistry::AddComponent(Entity entity, const C& component)
    {
        TName name = GetComponentTI<C>().name();

        if (!m_componentBitPosition.contains(name))
        {
            m_componentBitPosition.emplace(name, m_componentPools.size());
            m_componentPools.push_back(MakeUnique<EntitySparseSet<C>>());
        }

        EntitySparseSet<C>& container = GetContainer<C>(true);
        NCHECK(!container.Get(entity))
        ComponentMask& mask = GetEntityMask(entity);

        RemoveFromGroup(mask, entity);
        SetComponentBit<C>(mask, 1);
        AssignToGroup(mask, entity);

        return *container.Add(entity, component);
    }

    template<typename C>
    void EntityRegistry::RemoveComponent(Entity entity, const C& component)
    {
        EntitySparseSet<C>& container = GetContainer<C>(true);
        NCHECK(!container.Get(entity))
        ComponentMask& mask = GetEntityMask(entity);

        RemoveFromGroup(mask, entity);
        SetComponentBit<C>(mask, 0);
        AssignToGroup(mask, entity);

        container.Remove(entity);
    }

    template<typename... C>
    bool EntityRegistry::HasComponents(Entity entity)
    {
        return (HasComponent<C>(entity) && ...);
    }

    template<typename C>
    bool EntityRegistry::HasComponent(Entity entity)
    {
        auto& container = GetContainer<C>();
        return container.Get(entity) ? true : false;
    }

    template<typename... C>
    std::vector<Entity> EntityRegistry::GetEntities()
    {
        std::vector<Entity> result;
        ComponentMask targetMask = GetMask<C...>();

        for (auto& [mask, ids]: m_groupings)
        {
            if ((mask & targetMask) == targetMask)
            {
                result.insert(result.end(), ids.Values().begin(), ids.Values().end());
            }
        }

        return result;
    }

    template<typename... C>
    std::vector<std::tuple<Entity, C&...>> EntityRegistry::View()
    {
        std::vector<std::tuple<Entity, C&...>> result;
        ComponentMask targetMask = GetMask<C...>();

        for (auto& [mask, ids]: m_groupings)
        {
            if (mask == targetMask)
            {
                for (const Entity& id : ids.Values())
                {
                    result.emplace_back(id, GetComponent<C>(id)...);
                }
            }
        }

        return result;
    }

    template<typename C>
    std::size_t EntityRegistry::GetComponentBitPosition()
    {
        TName name = GetComponentTI<C>().name();
        auto it = m_componentBitPosition.find(name);
        if (it == m_componentBitPosition.end())
        {
            return GMaxTIndex;
        }

        return it->second;
    }

    template<typename C>
    EntitySparseSet<C>& EntityRegistry::GetContainer(bool registerIfNotFound)
    {
        std::size_t bitPos = GetComponentBitPosition<C>();

        if (bitPos == GMaxTIndex)
        {
            TName name = GetComponentTI<C>().name();
            m_componentBitPosition.emplace(name, m_componentPools.size());
            m_componentPools.push_back(MakeUnique<EntitySparseSet<C>>());
            bitPos = GetComponentBitPosition<C>();
        }

        NCHECK(bitPos < m_componentPools.size() && bitPos >= 0);

        Container<Entity>& container = *m_componentPools[bitPos];
        EntitySparseSet<C>& pool = static_cast<EntitySparseSet<C>&>(container);

        return pool;
    }

    template<typename C>
    void EntityRegistry::SetComponentBit(ComponentMask& mask, bool val)
    {
        std::size_t bitPos = GetComponentBitPosition<C>();
        NCHECK(bitPos != GMaxTIndex);
        mask[bitPos] = val;
    }

    template<typename C>
    EntityRegistry::ComponentMask::reference EntityRegistry::GetComponentBit(
            ComponentMask& mask)
    {
        std::size_t bitPos = GetComponentBitPosition<C>();
        NCHECK(bitPos != GMaxTIndex);
        return mask[bitPos];
    }

    template<typename... C>
    EntityRegistry::ComponentMask EntityRegistry::GetMask()
    {
        ComponentMask mask;
        (SetComponentBit<C>(mask, 1), ...);
        return mask;
    }


}// namespace Nenuphar
