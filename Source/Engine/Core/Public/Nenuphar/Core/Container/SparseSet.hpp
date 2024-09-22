#pragma once

#undef max

#include "Nenuphar/Core/Core.hpp"

#include <utility>
#include <vector>
#include <limits>

namespace Nenuphar
{

    static constexpr std::size_t GMaxTIndex = 
        std::numeric_limits<std::size_t>::max();

    template<typename TId>
    class Container
    {
    public:
        
        using TIndex = std::size_t;

    public:
        virtual void Remove(TId id) = 0;

    public:
        virtual ~Container() = default;

    };

    template<typename TId,
             typename TValue,
             std::size_t MaxNumPage = 100>
    class SparseSet : public Container<TId>
    {
        using TSuper = Container<TId>;
        using TIndex = TSuper::TIndex;
        using Sparse = std::vector<TIndex>;

    public:
        TValue* Add(TId id, const TValue& value);
        TValue* Get(TId id);
        virtual void Remove(TId id) override;

        inline const std::vector<TValue>& Values();
        inline bool IsEmpty();

    public:
		SparseSet() { m_denseValue.reserve(100); }
        virtual ~SparseSet() override = default;

    private:
        void SetDenseIndex(TId id, TIndex index);

        TIndex GetDenseIndex(TId id);

    private:
        std::vector<Sparse> m_sparses;
        std::vector<TValue> m_denseValue;
        std::vector<TId> m_denseIdentification;
    };

    template<typename TId, typename TValue, std::size_t MaxNumPage>
    inline const std::vector<TValue>& SparseSet<TId, TValue, MaxNumPage>::Values()
    {
        return m_denseValue;
    }


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
            sparse.resize(sparseIndex + 1, GMaxTIndex);
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

        return GMaxTIndex;
    }


    template<typename TId, typename TValue, std::size_t MaxNumPage>
    TValue* SparseSet<TId, TValue, MaxNumPage>::Add(TId id, const TValue& value)
    {
        size_t index = GetDenseIndex(id);
        if (index != GMaxTIndex)
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
        return (index != GMaxTIndex) ? &m_denseValue[index] : nullptr;
    }


    template<typename TId, typename TValue, std::size_t MaxNumPage>
    void SparseSet<TId, TValue, MaxNumPage>::Remove(TId id)
    {
        TIndex deletedIndex = GetDenseIndex(id);
        NCHECK(deletedIndex != GMaxTIndex && !m_denseValue.empty());

        SetDenseIndex(m_denseIdentification.back(), deletedIndex);
        SetDenseIndex(id, GMaxTIndex);

        auto tmp = std::move(m_denseValue.back());
        auto left = std::move(m_denseValue[deletedIndex]);
        auto right = std::move(tmp);

        // std::swap(m_denseValue.back(), m_denseValue[deletedIndex] );
        std::swap(m_denseIdentification.back(), m_denseIdentification[deletedIndex]);

        m_denseValue.pop_back();
        m_denseIdentification.pop_back();
    }

    template<typename TId, typename TValue, std::size_t MaxNumPage>
    inline bool SparseSet<TId, TValue, MaxNumPage>::IsEmpty()
    {
        return m_denseValue.empty();
    }

}// namespace Nenuphar
