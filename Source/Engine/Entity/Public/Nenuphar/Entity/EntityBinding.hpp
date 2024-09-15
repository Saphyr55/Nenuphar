#pragma once

#include "Nenuphar/Entity/Entity.hpp"
#include "Nenuphar/Entity/MemoryComponentSector.hpp"

#include <unordered_map>

namespace Nenuphar
{
    class EntityBinding
    {
    public:
        using MemorySectorOfEntity = std::unordered_map<Entity, MemorySectorBinding>;

        inline MemorySectorBinding& SectorOfEntity(const Entity& entity);

        inline MemorySectorOfEntity& SectorOfEntity();

    private:
        MemorySectorOfEntity m_sectorOfEntity{};
    };

    EntityBinding::MemorySectorOfEntity& EntityBinding::SectorOfEntity()
    {
        return m_sectorOfEntity;
    }

    MemorySectorBinding& EntityBinding::SectorOfEntity(const Entity& entity)
    {
        return m_sectorOfEntity.at(entity);
    }


}