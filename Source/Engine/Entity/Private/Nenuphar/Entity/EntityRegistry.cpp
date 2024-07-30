#include "Nenuphar/Entity/EntityRegistry.hpp"


namespace Nenuphar
{

    MemoryComponentSector& EntityRegistry::AddNode(MemoryComponentLayout layout)
    {
        MemoryComponentLayout& signature = layout;
        MemoryComponentLayout newLayout;
        ComponentTI lastCti = signature[0];

        auto& last = RootSector();
        auto& it = RootSector();

        std::size_t depth = 0;
        for (const auto& cti: layout)
        {
            newLayout.push_back(cti);
            auto& edges = it.Edges();

            if (!edges.contains(cti))
            {
                MemoryComponentSectorEdge edge;
            }
        }

        return it;
    }

    Entity EntityRegistry::Create()
    {
        Entity entity = m_entities.size();
        m_entities.emplace(entity);

        MemoryComponentSector& sector = *m_sectors[0];

        MemorySectorBinding binding(sector.Id(), sector.Extends());
        m_entityBinding.SectorOfEntity().insert({ entity, binding});

        return entity;
    }

    EntityRegistry::EntityRegistry()
        : m_sectors()
        , m_entities()
        , m_sectorByComponent()
        , m_entityBinding()
    {
        auto sector = MakeUnique<MemoryComponentSector>(0, MemoryComponentLayout());
        m_sectors.insert({ 0, std::move(sector) });
    }

    void EntityRegistry::Remove(Entity entity)
    {
    }

    MemoryComponentSector& EntityRegistry::GetSector(MemorySectorId id)
    {
        return *m_sectors[id];
    }

    MemoryComponentSector& EntityRegistry::RootSector()
    {
        return GetSector(0);
    }


}
