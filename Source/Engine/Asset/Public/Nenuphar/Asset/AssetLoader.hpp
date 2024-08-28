#pragma once

#include "Nenuphar/Asset/Asset.hpp"
#include "Nenuphar/Common/Type/Type.hpp"
#include "Nenuphar/Core/IO/Path.hpp"


namespace Nenuphar
{

    class IAssertLoader
    {
    public:
        virtual SharedRef<Asset> LoadAsset(const Path& path) const = 0;

        virtual void UnloadAsset(SharedRef<Asset> asset) const = 0;
    };

    template<CIsAsset A>
    class AssetLoader : public IAssertLoader
    {
    public:
        virtual SharedRef<A> Load(const Path& path) const = 0;

        virtual void Unload(SharedRef<A> asset) const = 0;

        virtual SharedRef<Asset> LoadAsset(const Path& path) const override;

        virtual void UnloadAsset(SharedRef<Asset> asset) const override;
    };

    template<CIsAsset A>
    SharedRef<Asset> AssetLoader<A>::LoadAsset(const Path& path) const
    {
        return Load(path);
    }

    template<CIsAsset A>
    void AssetLoader<A>::UnloadAsset(SharedRef<Asset> asset) const
    {
        Unload(std::static_pointer_cast<A>(asset));
    }

}