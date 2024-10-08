#pragma once

#include "Nenuphar/Common/Type/Type.hpp"
#include "Nenuphar/Entity/ComponentBuffer.hpp"


namespace Nenuphar
{

    /**
     *
     */
    using MemorySectorId = UInt32;

    /**
     *
     */
    using MemoryComponentLayout = std::vector<ComponentTI>;

    template<typename ...T>
    inline MemoryComponentLayout MakeMemoryComponentLayout()
    {
        return { GetComponentTI<T>()... };
    }

    /**
     *
     */
    using MemorySectorMap = std::unordered_map<MemorySectorId, ComponentTIBinding>;

    /**
     *
     */
    struct MemoryComponentSector;

    /**
     * Structure which links something to the corresponding memory sector,
     * using the index.
     */
    struct MemorySectorBinding
    {
        // The identifier of the sector containing the current entity.
        MemorySectorId SectorId;
        // The column number in the memory sector.
        std::size_t Column;
    };

    /**
     *
     */
    struct MemoryComponentSectorEdge
    {
        MemorySectorId Add;
        MemorySectorId Remove;
    };


    /**
     *
     */
    class MemoryComponentSector
    {
        using GraphEdges = std::unordered_map<ComponentTI, MemoryComponentSectorEdge>;

        using ComponentTIMapping = std::unordered_map<ComponentTI, MemorySectorMap>;

    public:

        /**
         *
         * @return
         */
        static MemoryComponentSector Empty();

        /**
         * Get
         * @return
         */
        [[nodiscard]] inline MemorySectorId Id() const { return m_sectorId; }

        /**
         *
         * @return
         */
        [[nodiscard]] inline std::size_t Size() const { return m_count; }

        /**
         *
         * @return
         */
        inline std::vector<ComponentBuffer>& ComponentStorages() { return m_buffers; }

        /**
         *
         * @param row
         * @return
         */
        ComponentBuffer& BufferAt(std::size_t index);

        /**
         *
         * @param cti
         * @param bufferElementSize
         */
        void AddBuffer(ComponentTI cti, std::size_t bufferElementSize);

        /**
         *
         * @return
         */
        inline MemoryComponentLayout& Layout() { return m_layout; }

        /**
         *
         * @return
         */
        inline GraphEdges& Edges() { return m_edges; }

        /**
         *
         * @param componentTi
         * @return
         */
        MemoryComponentSectorEdge& Edge(ComponentTI& componentTi);

        /**
         *
         * @param index
         * @return
         */
        ComponentBuffer& operator[](std::size_t index);

        /**
         *
         * @param cti
         * @return
         */
        std::size_t IndexOf(ComponentTI cti) const;

        /**
         *
         * @return
         */
        std::size_t Extends();

        /**
         * @brief Construct a Memory Component Sector instance.
         * 
         * @param id 
         * @param layout 
         */
        MemoryComponentSector(MemorySectorId id, MemoryComponentLayout layout);

        /**
         * @brief Delete the copy of a new Memory Component Sector instance.
         * 
         */
        MemoryComponentSector(const MemoryComponentSector&) = delete;

        /**
         * @brief Delete the move of a Memory Component Sector instance.
         * 
         */
        MemoryComponentSector(MemoryComponentSector&&) = delete;

        /**
         * @brief Default Memory Component Sector destructor.
         * 
         */
        ~MemoryComponentSector() = default;

    private:
        // The identifier of this sector.
        MemorySectorId m_sectorId;
        // The memory matrix.
        //
        //   0 1 2 <- Index for the entities.
        // 0 A A A <-- Buffer.
        // 1 A A A
        // 2 A A A
        // ^
        // |
        // Indices for the component buffer.
        std::vector<ComponentBuffer> m_buffers;
        // The memory component layout.
        MemoryComponentLayout m_layout;
        //
        std::size_t m_count;
        // Graph component.
        GraphEdges m_edges;
    };

}

