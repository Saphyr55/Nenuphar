#pragma once

#include "Nenuphar/Asset/Asset.hpp"
#include "Nenuphar/Common/Container/SparseSet.hpp"
#include "Nenuphar/Common/Type/Type.hpp"


namespace Nenuphar
{

    class AssetRegistry
    {
    public:
        using TStorage = SparseSet<AssetId, AssetMetadata>;

        static SharedRef<AssetRegistry> Instance();

    private:
        TStorage m_storage;
        static AssetRegistry s_mainStorage;
    };

}// namespace Nenuphar