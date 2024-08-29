#pragma once

#include "Nenuphar/Entity/ComponentBuffer.hpp"


namespace Nenuphar
{

    /**
     *
     */
    using MemorySectorId = Word32;

    /**
     *
     */
    using MemoryComponentLayout = std::vector<ComponentTI>;

    template<typename ...T>
    MemoryComponentLayout MakeMemoryComponentLayout()
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
        Word Column;
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
        [[nodiscard]] inline Word Size() const { return m_count; }

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
        ComponentBuffer& BufferAt(Word index);

        /**
         *
         * @param cti
         * @param bufferElementSize
         */
        void AddBuffer(ComponentTI cti, Word bufferElementSize);

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
        ComponentBuffer& operator[](Word index);

        /**
         *
         * @param cti
         * @return
         */
        Word IndexOf(ComponentTI cti) const;

        /**
         *
         * @return
         */
        Word Extends();

        /**
         *
         * @param id
         * @param layout
         */
        MemoryComponentSector(MemorySectorId id, MemoryComponentLayout layout);


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
        Word m_count;
        // Graph component.
        GraphEdges m_edges;
    };

}

