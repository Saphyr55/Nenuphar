#pragma once

#include "Nenuphar/Common/Type/Type.hpp"
#include "Nenuphar/Model/ModelAsset.hpp"
#include "Nenuphar/Model/ModelLoader.hpp"

#include <optional>

namespace Nenuphar
{

    class ObjModelLoader
    {
    public:
        virtual ModelLoader::TRes Load(const Path& path,
                                       const ModelAssetOptions& options) const;

        static UniquePtr<ObjModelLoader> Create();

    };

}