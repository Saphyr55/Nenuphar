#pragma once

#include "Nenuphar/Asset/Asset.hpp"
#include "Nenuphar/Common/Container/SparseSet.hpp"
#include "Nenuphar/Common/Type/Type.hpp"


namespace Nenuphar
{
    
    class AssetRegistry
    {

        template<typename T>
        using TStorage = SparseSet<AssetHandle, T>;

        using TMetadataStorage = TStorage<AssetMetadata>;

        using TAssetStorage = TStorage<SharedRef<Asset>>;

    public:
        
        static SharedRef<AssetRegistry> Instance();
    
    private:
        TAssetStorage m_assets;
        TMetadataStorage m_metadataStorage;
        static AssetRegistry s_mainStorage;
    };

}// namespace Nenuphar