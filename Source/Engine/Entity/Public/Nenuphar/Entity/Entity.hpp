//
// Created by admin on 14/04/2024.
//

#pragma once

#ifndef NP_ENTITY_HPP
#define NP_ENTITY_HPP

#include "Nenuphar/Core/Core.hpp"

#include <typeindex>
#include <algorithm>
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
    using ArchetypeIndices = std::vector<ComponentIndex>;

    /**
     *
     */
    using ArchetypeID = std::size_t;

    /**
     *
     */
    struct ArchetypeRecord
    {
        std::size_t Column;
    };

    /**
     *
     */
    using ArchetypeMap = std::unordered_map<ArchetypeID, ArchetypeRecord>;

    /**
     *
     */
    using Column = std::vector<void*>;

    /**
     *
     */
    struct Archetype
    {
        ArchetypeIndices Indices;
        ArchetypeID ID;
        std::vector<Column> Components;
    };

    struct Record
    {
        Record();

        Archetype& Archetype;
        std::size_t Row;
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
        EntityRegistry() = default;
        ~EntityRegistry() = default;

    private:
        std::unordered_map<ComponentIndex, ArchetypeMap> m_componentsIndex;
        std::unordered_map<Entity, Record> m_entityArchetypes;
        std::vector<Entity> m_entities;
    };


    template<typename C>
    void EntityRegistry::AddComponent(Entity entity, C&& component)
    {

    }

    template<typename C>
    bool EntityRegistry::HasComponent(Entity entity)
    {
        ComponentIndex componentIndex = GetComponentIndex<C>();
        Archetype& archetype = m_entityArchetypes[entity].Archetype;
        ArchetypeMap& archetype_set = m_componentsIndex[componentIndex];
        return archetype_set.count(archetype.ID) != 0;
    }

    template<typename C>
    C& EntityRegistry::GetComponent(Entity entity)
    {

        ComponentIndex componentIndex = GetComponentIndex<C>();
        Record& record = m_entityArchetypes[entity];
        Archetype& archetype = record.Archetype;

        // First check if archetype has component
        ArchetypeMap archetypes = m_componentsIndex[componentIndex];

        if (archetypes.count(archetype.ID) == 0)
        {
            return nullptr;
        }

        ArchetypeRecord& a_record = archetypes[archetype.ID];
        VoidPtr component = archetype.Components[a_record.Column][record.Row];
        return *dynamic_cast<C>(component);
    }


}


#endif //NP_ENTITY_HPP
