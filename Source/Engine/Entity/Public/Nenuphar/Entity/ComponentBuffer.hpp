#pragma once

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
        template<Word MaxAmount>
        class ComponentBufferBase
        {
        public:
            /**
             *
             */
            static constexpr Word MaxAmountValue = MaxAmount;

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
            [[nodiscard]] Word Size() const;

            /**
             *
             * @param index
             * @return
             */
            void* DataAt(Word index);

            /**
             *
             * @tparam T
             * @param component
             * @param index
             * @return
             */
            template<typename T>
            Word Insert(Word index, T component);

            /**
             *
             * @param component
             * @param index
             * @return
             */
            Word Insert(Word index, void* component);

            /**
             *
             * @param index
             */
            void DeleteAt(Word index);

            /**
             *
             * @param cti
             * @param elementSize
             */
            ComponentBufferBase(ComponentTI cti, Word elementSize);

        private:
            Word m_elementSize;
            Word m_count;
            std::unique_ptr<Buffer> m_elements;
            ComponentTI m_cti;
        };

        template<Word MaxAmount>
        Word ComponentBufferBase<MaxAmount>::Insert(Word index, void* component)
        {
            std::memcpy(DataAt(index), component, m_elementSize);
            m_count++;
            return m_count - 1;
        }

        template<Word MaxAmount>
        template<typename T>
        Word ComponentBufferBase<MaxAmount>::Insert(Word index, T component)
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

        template<Word MaxAmount>
        void* ComponentBufferBase<MaxAmount>::DataAt(Word index)
        {
            return &m_elements[index * m_elementSize];
        }

        template<Word MaxAmount>
        Word ComponentBufferBase<MaxAmount>::Size() const
        {
            return m_count;
        }

        template<Word MaxAmount>
        void ComponentBufferBase<MaxAmount>::DeleteAt(Word index)
        {
            m_elements.get()[index * m_elementSize] = 0;
        }

        template<Word MaxAmount>
        ComponentBufferBase<MaxAmount>::ComponentBufferBase(ComponentTI cti, Word elementSize)
            : m_elementSize(elementSize)
            , m_count(0)
            , m_elements(new Word8[MaxAmount * m_elementSize])
            , m_cti(cti)
        {
        }

    }// namespace Details

    using ComponentBuffer = Details::ComponentBufferBase<10'000>;

}// namespace Nenuphar