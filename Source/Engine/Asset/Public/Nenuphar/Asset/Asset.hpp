#pragma once

#include "Nenuphar/Common/Type/Type.hpp"
#include "Nenuphar/Core/IO/Path.hpp"
#include <type_traits>

namespace Nenuphar
{
    
    using AssetHandle = std::size_t;
    
    class Asset
    {
    public:
        Asset() = default;
        virtual ~Asset() = default;
    };

    template<typename A>
    concept CIsAsset = std::is_base_of_v<Asset, A>;

    class AssetMetadata
    {

        Path FilePath;
    };

    Path FromProject(StringView path);

    Path FromAssets(StringView path);
}