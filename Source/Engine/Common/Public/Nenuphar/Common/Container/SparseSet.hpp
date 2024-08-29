#pragma once

#include <vector>

namespace Nenuphar
{

    
    
    template<typename TId,
             typename TValue,
             std::size_t MaxNumPage = 100>
    class SparseSet
    {
        using TIndex = std::size_t;

        using Sparse = std::vector<TIndex>;

        static constexpr size_t MaxTIndex =
                std::numeric_limits<TIndex>::max();

    public:
        TValue* Add(TId id, TValue&& value);
        TValue* Get(TId id);
        void Remove(TId id);
        
    private:
        void SetDenseIndex(TId id, TIndex index);

        TIndex GetDenseIndex(TId id);

    private:
        std::vector<Sparse> m_sparses;
        std::vector<TValue> m_denseValue;
        std::vector<TId> m_denseIdentification;
    };


    template<typename TId, typename TValue, std::size_t MaxNumPage>
    void SparseSet<TId, TValue, MaxNumPage>::SetDenseIndex(TId id, TIndex index)
    {
        std::size_t page = id / MaxNumPage;
        std::size_t sparseIndex = id % MaxNumPage;

        if (page >= m_sparses.size())
        {
            m_sparses.resize(page + 1);
        }

        Sparse& sparse = m_sparses[page];
        if (sparseIndex >= sparse.size())
        {
            sparse.resize(sparseIndex + 1, MaxTIndex);
        }

        sparse[sparseIndex] = index;
    }


    template<typename TId, typename TValue, std::size_t MaxNumPage>
    auto SparseSet<TId, TValue, MaxNumPage>::GetDenseIndex(TId id) -> TIndex
    {
        std::size_t page = id / MaxNumPage;
        std::size_t sparseIndex = id % MaxNumPage;

        if (page < m_sparses.size())
        {
            Sparse& sparse = m_sparses[page];
            if (sparseIndex < sparse.size())
            {
                return sparse[sparseIndex];
            }
        }

        return MaxTIndex;
    }


    template<typename TId, typename TValue, std::size_t MaxNumPage>
    TValue* SparseSet<TId, TValue, MaxNumPage>::Add(TId id, TValue&& value)
    {
        size_t index = GetDenseIndex(id);
        if (index != MaxTIndex)
        {
            m_denseValue[index] = value;
            m_denseIdentification[index] = id;

            return &m_denseValue[index];
        }

        SetDenseIndex(id, m_denseValue.size());

        m_denseValue.push_back(value);
        m_denseIdentification.push_back(id);

        return &m_denseValue.back();
    }


    template<typename TId, typename TValue, std::size_t MaxNumPage>
    TValue* SparseSet<TId, TValue, MaxNumPage>::Get(TId id)
    {
        TIndex index = GetDenseIndex(id);
        return (index != MaxTIndex) ? &m_denseValue[index] : nullptr;
    }


    template<typename TId, typename TValue, std::size_t MaxNumPage>
    void SparseSet<TId, TValue, MaxNumPage>::Remove(TId id)
    {
        TIndex deletedIndex = GetDenseIndex(id);
        CHECK(deletedIndex != MaxTIndex && !m_denseValue.empty());

        SetDenseIndex(m_denseIdentification.back(), deletedIndex);
        SetDenseIndex(id, MaxTIndex);

        std::swap(m_denseValue.back(), m_denseValue[deletedIndex]);
        std::swap(m_denseIdentification.back(), m_denseIdentification[deletedIndex]);

        m_denseValue.pop_back();
        m_denseIdentification.pop_back();
    }


} // namespace Nenuphar
