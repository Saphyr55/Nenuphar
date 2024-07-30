#include <utility>

#include "Nenuphar/Entity/MemoryComponentSector.hpp"

namespace Nenuphar
{

    MemoryComponentSector::MemoryComponentSector(MemorySectorId id, MemoryComponentLayout layout)
            : m_sectorId(id)
            , m_layout(layout)
            , m_count(0) 
    {

    }

    MemoryComponentSectorEdge& MemoryComponentSector::Edge(ComponentTI& componentTi)
    {
        return m_edges[componentTi];
    }

    ComponentBuffer& MemoryComponentSector::operator[](Word index)
    {
        if (index >= m_buffers.size())
        {
            NP_ERROR(MemoryComponentSector::operator[], "Index out of range: {}", index);
            throw std::exception();
        }

        return m_buffers[index];
    }

    Word MemoryComponentSector::IndexOf(ComponentTI cti) const
    {
        auto result = std::find(m_layout.begin(), m_layout.end(), cti);
        if (result == m_layout.end())
        {
            NP_ERROR(MemoryComponentSector::IndexOf,
                     "No index found for the component: {} in the sector: {}",
                     cti.name(), Id());

            throw std::exception();
        }

        return std::distance(m_layout.begin(), result);
    }

    void MemoryComponentSector::AddBuffer(ComponentTI cti, Word bufferElementSize)
    {
        m_buffers.emplace_back(cti, bufferElementSize);
    }

    Word MemoryComponentSector::Extends()
    {
        m_count++;
        return m_count - 1;
    }

    ComponentBuffer& MemoryComponentSector::BufferAt(Word index)
    {
        if (index >= m_buffers.size())
        {
            NP_ERROR(MemoryComponentSector::operator[], "Index out of range: {}", index);
            throw std::exception();
        }

        return m_buffers.at(index);
    }

    MemoryComponentSector MemoryComponentSector::Empty()
    {
        return MemoryComponentSector(0, { });
    }

}