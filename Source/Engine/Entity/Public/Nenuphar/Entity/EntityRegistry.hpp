#pragma once

#include "Nenuphar/Core/Core.hpp"
#include "Nenuphar/Entity/Entity.hpp"
#include "Nenuphar/Entity/ComponentTI.hpp"
#include "Nenuphar/Entity/MemoryComponentSector.hpp"
#include "Nenuphar/Entity/EntityBinding.hpp"

#include <typeindex>
#include <any>
#include <set>
#include <map>
#include <memory>

namespace Nenuphar
{


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
        void AddComponent(Entity entity, const C& component);

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
         *
         * @tparam C
         * @param entity
         * @return
         */
        template<typename C>
        C& GetComponent(Entity entity);

        /**
         *
         * @tparam T
         * @return
         */
        template<typename ...T>
        MemoryComponentSector& RegisterSector();

    private:

        MemoryComponentSector& RootSector();

        MemoryComponentSector& GetSector(MemorySectorId id);

        MemoryComponentSector& AddNode(MemoryComponentLayout layout);

    public:
        EntityRegistry();
        ~EntityRegistry() = default;

    private:
        using MemorySectorMap = std::unordered_map<MemorySectorId, ComponentTIBinding>;

        std::unordered_set<Entity> m_entities;

        EntityBinding m_entityBinding;

        std::unordered_map<MemorySectorId, Ptr<MemoryComponentSector>> m_sectors;

        std::map<MemoryComponentLayout, MemoryComponentSector&> m_layoutOfSector;
        std::unordered_map<ComponentTI, MemorySectorMap> m_sectorByComponent;
        std::unordered_map<ComponentTI, Word> m_componentSizeIndex;
    };

    template<typename ...T>
    MemoryComponentSector& EntityRegistry::RegisterSector()
    {
        MemorySectorId id = m_sectors.size();
        auto layout = MakeMemoryComponentLayout<T...>();
        auto sector = MakeUnique<MemoryComponentSector>(id, layout);

        m_sectors.insert({ id, std::move(sector) });
        return GetSector(id);
    }

    template<typename C>
    void EntityRegistry::RemoveComponent(Entity entity, const C& component)
    {

    }

    template<typename C>
    void EntityRegistry::AddComponent(Entity entity, const C& component)
    {
        ComponentTI componentTI = GetComponentTI<C>();
        auto& entityBinding = m_entityBinding.SectorOfEntity(entity);
        auto& sector = GetSector(entityBinding.SectorId);

        if (!m_componentSizeIndex.contains(componentTI))
        {
            m_componentSizeIndex[componentTI] = sizeof(C);
            m_sectorByComponent[componentTI] = { };
        }

        if (!sector.Edges().contains(componentTI))
        {
            // TODO: Better Id.
            auto nextSectorId = MemorySectorId(m_sectors.size());

            MemoryComponentLayout nextLayout(sector.Layout());
            nextLayout.push_back(componentTI);
    
            auto nextSector = MakeUnique<MemoryComponentSector>(nextSectorId, nextLayout);

            for (const auto& buffer : sector.ComponentStorages())
            {
                auto cti = buffer.CTI();
                nextSector->AddBuffer(cti, m_componentSizeIndex[cti]);

                auto index = nextSector->IndexOf(cti);
                m_sectorByComponent[cti][nextSectorId] = { index };
            }

            nextSector->AddBuffer(componentTI, m_componentSizeIndex[componentTI]);

            m_sectorByComponent[componentTI][nextSectorId] = { nextSector->IndexOf(componentTI) };
            
            m_sectors.emplace(nextSectorId, std::move(nextSector));

            sector.Edge(componentTI).Add = nextSectorId;
        }

        auto& sectorsBinding = m_sectorByComponent[componentTI];
        MemorySectorId& nextSectorId = sector.Edge(componentTI).Add;
        MemoryComponentSector& nextSector = GetSector(nextSectorId);
        ComponentTIBinding& componentBinding = sectorsBinding[nextSectorId];
        Word row = componentBinding.Row;
        Word column = entity;

        entityBinding.SectorId = nextSector.Id();
        // TODO: Must be indexed.
        entityBinding.Column = column;

        ComponentBuffer& buffer = nextSector.BufferAt(row);

        int index = 0;
        for (auto& item: sector.ComponentStorages())
        { 
            ComponentBuffer& buf = nextSector.BufferAt(index);
            void* data = item.DataAt(column);
            buf.Insert(column, data);
            item.DeleteAt(column);
            index++;
        }

        buffer.Insert<C>(column, component);
    }

    template<typename C>
    bool EntityRegistry::HasComponent(Entity entity)
    {
        ComponentTI componentTI = GetComponentTI<C>();
        auto& [sectorId, _] = m_entityBinding.SectorOfEntity(entity);
        MemorySectorMap& sectors = m_sectorByComponent[componentTI];

        return sectors.contains(sectorId);
    }

    template<typename C>
    C& EntityRegistry::GetComponent(Entity entity)
    {
        ComponentTI componentTI = GetComponentTI<C>();
        auto& [sectorId, column] = m_entityBinding.SectorOfEntity(entity);
        MemorySectorMap& sectors = m_sectorByComponent[componentTI];

        if (!sectors.contains(sectorId))
        {
            NP_ERROR(EntityRegistry::GetComponent, "The entity:{} haven't the component:{}",
                     entity, componentTI.name());
            throw std::exception();
        }

        auto& [row] = sectors[sectorId];
        auto& sector = GetSector(sectorId);

        ComponentBuffer& buffer = sector.BufferAt(row);

        void* data = buffer.DataAt(column);
        return *(static_cast<C*>(data));
    }



}

