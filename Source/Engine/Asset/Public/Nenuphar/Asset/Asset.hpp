#pragma once

#include "Nenuphar/Common/Type/Type.hpp"
#include "Nenuphar/Core/IO/Path.hpp"

#include <type_traits>

namespace Nenuphar
{
    
    using AssetHandle = std::size_t;

    class Asset;
    class AssetOptions;

    template<typename A>
    concept CIsAsset = std::is_base_of_v<Asset, A>;

    template<typename A>
    concept CIsAssetOptions = std::is_base_of_v<AssetOptions, A>;

    
    class Asset
    {
    public:
        constexpr Asset() = default;
        constexpr explicit Asset(const AssetHandle& handle);
        virtual ~Asset() = default;

        inline AssetHandle GetHandle();

    private:
        AssetHandle m_handle;
    };

    
    class AssetOptions
    {
    public:
        AssetOptions() = default;
        virtual ~AssetOptions() = default;
    };

    
    struct AssetMetadata
    {
        AssetHandle Handler;
        Path FilePath;
    };

    
    Path FromProject(StringView path);

    Path FromAssets(StringView path);
    
}