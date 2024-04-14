//
// Created by admin on 14/04/2024.
//

#pragma once

#ifndef NP_ENTITY_HPP
#define NP_ENTITY_HPP

#include "Nenuphar/Core/Core.hpp"

#include <typeindex>
#include <any>
#include <unordered_set>

namespace Nenuphar
{

    /**
     *
     */
    using Entity = std::size_t;

    /**
     *
     */
    using ComponentIndex = std::type_index;

    template<typename C>
    ComponentIndex GetComponentIndex()
    {
        return typeid(C);
    }

    /**
     *
     */
    using ComponentIndices = std::unordered_set<ComponentIndex>;

    using ArchetypeID = std::size_t;

    /**
     *
     */
    struct Components
    {
        std::unordered_map<ComponentIndex, std::any> Elements;
    };

    /**
     *
     */
    struct Archetype
    {
        ComponentIndices Indices;
    };

    /**
     *
     */
    struct Record
    {
        Archetype& Archetype;
        Components Components;
    };

    /**
     *
     */
    class EntityRegistry
    {
    public:

        /**
         *
         * @return
         */
        Entity Create();

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
        void AddComponent(Entity entity, C&& component);

        /**
         *
         * @tparam C
         * @param entity
         * @param component
         */
        template<typename C>
        void RemoveComponent(Entity entity, C&& component);

        /**
         *
         * @tparam C
         * @param entity
         * @return
         */
        template<typename C>
        bool HasComponent(Entity entity);

        /**
         *
         * @tparam C
         * @param entity
         * @return
         */
        template<typename C>
        C& GetComponent(Entity entity);

    public:
        EntityRegistry();
        ~EntityRegistry() = default;

    private:
        static Entity LastEntity;
        static ArchetypeID LastArchetype;

        std::vector<Entity> m_entities;
        std::unordered_set<Archetype> m_archetypes;
        std::unordered_map<ComponentIndex, Archetype> m_componentsIndex;
        std::unordered_map<Entity, Record> m_entityArchetypes;
    };

    template<typename C>
    void EntityRegistry::RemoveComponent(Entity entity, C&& component)
    {
        ComponentIndex componentIndex = GetComponentIndex<C>();
        Record& record = m_entityArchetypes[entity];
        Components& components = record.Components;

        Archetype& oldArchetype = m_archetypes[record.ArchetypeID];

        ComponentIndices componentsIndices = oldArchetype.Indices;
        componentsIndices.erase(componentIndex);

        Archetype newArchetype(m_archetypes.size(), componentsIndices);

        ArchetypeID newArchetypeID = ++LastArchetype;

        m_archetypes[newArchetypeID] = newArchetype;
        m_componentsIndex[componentIndex] = newArchetypeID;
        record.ArchetypeID = newArchetypeID;

        components.Elements[componentIndex] = std::forward<C>(component);
    }

    template<typename C>
    void EntityRegistry::AddComponent(Entity entity, C&& component)
    {
        ComponentIndex componentIndex = GetComponentIndex<C>();
        Record& record = m_entityArchetypes[entity];
        Components& components = record.Components;

        Archetype& oldArchetype = m_archetypes[record.ArchetypeID];

        ComponentIndices componentsIndices = oldArchetype.Indices;
        componentsIndices.insert(componentIndex);

        Archetype newArchetype(m_archetypes.size(), componentsIndices);

        ArchetypeID newArchetypeID = ++LastArchetype;

        m_archetypes[newArchetypeID] = newArchetype;
        m_componentsIndex[componentIndex] = newArchetypeID;
        record.ArchetypeID = newArchetypeID;

        components.Elements[componentIndex] = std::forward<C>(component);
    }

    template<typename C>
    bool EntityRegistry::HasComponent(Entity entity)
    {
        ComponentIndex componentIndex = GetComponentIndex<C>();
        Record& record = m_entityArchetypes[entity];
        Archetype& archetype = record.Archetype;
        return archetype.Indices.contains(componentIndex);
    }

    template<typename C>
    C& EntityRegistry::GetComponent(Entity entity)
    {
        ComponentIndex componentIndex = GetComponentIndex<C>();
        std::any& any = m_entityArchetypes[entity].Components.Elements[componentIndex];
        if (!any.has_value())
        {
            throw std::exception();
        }
        return std::any_cast<C&>(any);
    }


}


#endif //NP_ENTITY_HPP
