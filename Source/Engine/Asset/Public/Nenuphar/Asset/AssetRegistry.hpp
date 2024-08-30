#pragma once

#include "Asset.hpp"
#include "AssetLoader.hpp"
#include "Nenuphar/Asset/Asset.hpp"
#include "Nenuphar/Asset/AssetLoader.hpp"
#include "Nenuphar/Common/Container/SparseSet.hpp"
#include "Nenuphar/Common/Type/Type.hpp"
#include "Nenuphar/Core/Debug.hpp"
#include "Nenuphar/Core/IO/Path.hpp"
#include "Nenuphar/Core/Logger/Logger.hpp"


#include <memory>
#include <typeindex>
#include <unordered_map>


namespace Nenuphar
{

    class AssetRegistry
    {
        template<typename T>
        using TStorage = SparseSet<AssetHandle, T>;

        using TMetadataStorage = TStorage<AssetMetadata>;
        using TAssetStorage = TStorage<SharedRef<Asset>>;

        using TTypeLoaderMapping = std::unordered_map<std::type_index,
                                                      SharedRef<AssertLoader>>;

        using THandles = std::unordered_map<std::string, AssetHandle>;

    public:
        static AssetRegistry& Instance();

        template<CIsAsset A, CIsAssetOptions Options = AssetOptions>
        void AddLoader(SharedRef<AssetLoader<A, Options>> loader);

        template<CIsAsset A>
        SharedRef<AssetLoader<A>> GetLoader();

        template<CIsAsset A, CIsAssetOptions Options = AssetOptions>
        SharedRef<A> Load(std::string_view vpath,
                          const Options& options = Options());

        template<CIsAsset A>
        void Unload(SharedRef<A> asset);

        template<CIsAsset A>
        void Unload(std::string_view vpath);

    private:
        THandles m_handlersFile;
        TTypeLoaderMapping m_loaders;
        TAssetStorage m_assets;
        TMetadataStorage m_metadataStorage;
        AssetHandle m_lastHandle;

        static AssetRegistry s_mainRegistry;
    };


    template<CIsAsset A>
    void AssetRegistry::Unload(SharedRef<A> asset)
    {
        AssetHandle handle = asset->GetHandle();
        AssetMetadata* metadata = m_metadataStorage.Get(handle);
        if (!metadata)
        {
            return;
        }

        m_handlersFile.erase(metadata->FilePath.GetFilePath());
        m_assets.Remove(handle);
        m_metadataStorage.Remove(handle);

        NCHECK(!metadata)

        m_loaders[typeid(A)]->UnloadAsset(asset);
    }


    template<CIsAsset A>
    SharedRef<AssetLoader<A>> AssetRegistry::GetLoader()
    {
        return std::static_pointer_cast<AssetLoader<A>>(m_loaders[typeid(A)]);
    }


    template<CIsAsset A, CIsAssetOptions Options>
    void AssetRegistry::AddLoader(SharedRef<AssetLoader<A, Options>> loader)
    {
        m_loaders[typeid(A)] = loader;
    }


    template<CIsAsset A, CIsAssetOptions Options>
    SharedRef<A> AssetRegistry::Load(std::string_view pathStrView,
                                     const Options& options)
    {
        if (!m_loaders.contains(typeid(A)))
        {
            NP_ERROR(AssetRegistry::Load, "No loader found for type asset '{}'.",
                     typeid(A).raw_name());
            NCHECK(false);
            return nullptr;
        }

        std::string pathStr(pathStrView);

        SharedRef<AssertLoader> loader = m_loaders.at(typeid(A));
        SharedRef<Asset> asset;

        if (!m_handlersFile.contains(pathStr))
        {
            Path path = FromAssets(pathStrView);
            asset = loader->LoadAsset(path, options);
            m_lastHandle++;
            m_handlersFile.insert({pathStr, m_lastHandle});
        }
        else
        {
            AssetHandle& handle = m_handlersFile.at(pathStr);
            asset = *m_assets.Get(handle);
        }

        return std::static_pointer_cast<A>(asset);
    }


}// namespace Nenuphar