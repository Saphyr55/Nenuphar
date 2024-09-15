#pragma once

#include "Nenuphar/Core/IO/Path.hpp"
#include "Nenuphar/Model/ModelAsset.hpp"
#include "Nenuphar/Model/ModelLoader.hpp"


namespace Nenuphar
{

    class TOLModelLoader
    {
    public:
        ModelLoader::TRes Load(const Path& path,
                               const TOLModelAssetOptions& options) const;
    };

}// namespace Nenuphar