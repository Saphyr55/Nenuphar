#pragma once

#include "Nenuphar/Asset/Asset.hpp"
#include "Nenuphar/Common/Type/Type.hpp"
#include "Nenuphar/Core/Core.hpp"
#include "Nenuphar/Core/IO/Path.hpp"


namespace Nenuphar
{

    class AssertLoader
    {
    public:
        virtual SharedRef<Asset> LoadAsset(
                const Path& path,
                const AssetOptions& options = AssetOptions()) = 0;

        virtual void UnloadAsset(SharedRef<Asset> asset) = 0;
    };

    template<CIsAsset A, CIsAssetOptions Options = AssetOptions>
    class AssetLoader : public AssertLoader
    {
    public:
        virtual SharedRef<A> Load(const Path& path,
                                  const Options& options);

        virtual void Unload(SharedRef<A> asset);

        virtual SharedRef<Asset> LoadAsset(
                const Path& path,
                const AssetOptions& options) override;

        virtual void UnloadAsset(SharedRef<Asset> asset) override;
    };

    template<CIsAsset A, CIsAssetOptions Options>
    SharedRef<A> AssetLoader<A, Options>::Load(const Path& path,
                                               const Options& options)
    {
        NCHECK(false)
        return nullptr;
    }

    template<CIsAsset A, CIsAssetOptions Options>
    void AssetLoader<A, Options>::Unload(SharedRef<A> asset) {
        NCHECK(asset)
    };

    template<CIsAsset A, CIsAssetOptions Options>
    SharedRef<Asset> AssetLoader<A, Options>::LoadAsset(
            const Path& path, const AssetOptions& options)
    {
        return Load(path, static_cast<const Options&>(options));
    }

    template<CIsAsset A, CIsAssetOptions Options>
    void AssetLoader<A, Options>::UnloadAsset(SharedRef<Asset> asset)
    {
        Unload(std::static_pointer_cast<A>(asset));
    }

}// namespace Nenuphar