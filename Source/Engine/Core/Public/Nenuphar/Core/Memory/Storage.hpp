#pragma once

#include <unordered_map>


namespace Nenuphar::Details
{

    template<typename K>
    struct StorageBase
    {

        /**
         *
         * @param key
         * @return
         */
        virtual void* DataAt(K key) = 0;

        /**
         *
         * @param key
         * @return
         */
        virtual void Replace(K key, void* value) = 0;

        /**
         *
         * @param key
         */
        virtual void Remove(K key) = 0;

        /**
         *
         * @param key
         * @return
         */
        virtual bool Has(K key) const = 0;

        /**
         *
         */
        virtual ~StorageBase() = default;

    };

    /**
     * Represent the component buffer, store all component by indices.
     */
    template<typename K, typename V>
    struct Storage : public Details::StorageBase<K>
    {
    public:

        virtual void* DataAt(K key) = 0;

        virtual void Replace(K key, void* value) = 0;

        virtual V& Assign(K key, V value) = 0;

        virtual V& Get(K key) = 0;

        virtual void Remove(K key) = 0;

        virtual bool Has(K key) const = 0;
    };

}


