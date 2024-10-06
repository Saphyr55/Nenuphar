#pragma once

#include "Nenuphar/Common/Type/Type.hpp"
#include "Nenuphar/Core/Memory/Storage.hpp"
#include "Nenuphar/Entity/ComponentTI.hpp"
#include "Nenuphar/Entity/Entity.hpp"

namespace Nenuphar
{

    namespace Details
    {

        /**
         *
         * @tparam MaxAmount
         */
        template<std::size_t MaxAmount>
        class ComponentBufferBase
        {
        public:
            /**
             *
             */
            static constexpr std::size_t MaxAmountValue = MaxAmount;

        public:
            /**
             * Get the component type index.
             * 
             * @return the component type index.
             */
            inline ComponentTI CTI() const
            {
                return m_cti;
            };

            /**
             * Get the size of the current buffer.
             *
             * @return the size.
             */
            [[nodiscard]] std::size_t Size() const;

            /**
             *
             * @param index
             * @return
             */
            void* DataAt(std::size_t index);

            /**
             *
             * @tparam T
             * @param component
             * @param index
             * @return
             */
            template<typename T>
            std::size_t Insert(std::size_t index, T component);

            /**
             *
             * @param component
             * @param index
             * @return
             */
            std::size_t Insert(std::size_t index, void* component);

            /**
             *
             * @param index
             */
            void DeleteAt(std::size_t index);

            /**
             *
             * @param cti
             * @param elementSize
             */
            ComponentBufferBase(ComponentTI cti, std::size_t elementSize);

        private:
            std::size_t m_elementSize;
            std::size_t m_count;
            std::unique_ptr<Word[]> m_elements;
            ComponentTI m_cti;
        };

        template<std::size_t MaxAmount>
        std::size_t ComponentBufferBase<MaxAmount>::Insert(std::size_t index, void* component)
        {
            std::memcpy(DataAt(index), component, m_elementSize);
            m_count++;
            return m_count - 1;
        }

        template<std::size_t MaxAmount>
        template<typename T>
        std::size_t ComponentBufferBase<MaxAmount>::Insert(std::size_t index, T component)
        {
            // We check if the buffer has exceeded the authorized component amount.
            // We raise an exception if this is the case.
            if (m_count == MaxAmount)
            {
                NP_ERROR(ComponentBufferBase::Insert,
                         "The buffer has exceeded the authorized component amount.");
                throw std::exception();
            }

            T(*array)
            [MaxAmount] = (T(*)[MaxAmount])m_elements.get();
            (*array)[index] = component;
            m_count++;

            return m_count - 1;
        }

        template<std::size_t MaxAmount>
        void* ComponentBufferBase<MaxAmount>::DataAt(std::size_t index)
        {
            return &m_elements[index * m_elementSize];
        }

        template<std::size_t MaxAmount>
        std::size_t ComponentBufferBase<MaxAmount>::Size() const
        {
            return m_count;
        }

        template<std::size_t MaxAmount>
        void ComponentBufferBase<MaxAmount>::DeleteAt(std::size_t index)
        {
            m_elements.get()[index * m_elementSize] = 0;
        }

        template<std::size_t MaxAmount>
        ComponentBufferBase<MaxAmount>::ComponentBufferBase(ComponentTI cti, std::size_t elementSize)
            : m_elementSize(elementSize)
            , m_count(0)
            , m_elements(new Word[MaxAmount * m_elementSize])
            , m_cti(cti)
        {
        }

    }// namespace Details

    using ComponentBuffer = Details::ComponentBufferBase<10'000>;

}// namespace Nenuphar