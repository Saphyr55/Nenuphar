#pragma once

#include "Nenuphar/Common/Container/SparseSet.hpp"
#include "Nenuphar/Common/Type/Type.hpp"
#include "Nenuphar/Resource/Resource.hpp"

namespace Nenuphar
{

    class ResourceRegistry
    {
    public:
        using TStorage = SparseSet<ResourceId, Resource>;

        static SharedRef<ResourceRegistry> Instance();

    private:
        TStorage m_storage;
        static ResourceRegistry s_mainStorage;
    };

}// namespace Nenuphar