#pragma once

#include "Nenuphar/Common/Type/Type.hpp"
#include "Nenuphar/Core/IO/Path.hpp"

namespace Nenuphar
{

    using AssetId = std::size_t;

    class AssetMetadata
    {
        Path FilePath;
    };

    Path FromProject(StringView path);

    Path FromAssets(StringView path);
}