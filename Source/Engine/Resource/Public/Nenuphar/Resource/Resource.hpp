#pragma once

#include "Nenuphar/Common/Type/Type.hpp"
#include "Nenuphar/Core/IO/Path.hpp"

namespace Nenuphar
{

    using ResourceId = std::size_t;

    class Resource
    {
        Path FilePath;
    };

    Path FromProject(StringView path);

    Path FromAssets(StringView path);
}