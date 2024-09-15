#pragma once

#include "Nenuphar/Asset/Asset.hpp"
#include "Nenuphar/Asset/AssetLoader.hpp"
#include "Nenuphar/Common/Type/Result.hpp"
#include "Nenuphar/Core/IO/Path.hpp"
#include "Nenuphar/Model/Model.hpp"
#include "Nenuphar/Model/ModelAsset.hpp"


#include <optional>

namespace Nenuphar
{

    enum class ModelLoaderError
    {
        PathNotExist,
        MalFormat
    };


    class ModelLoader
    {
    public:
        using TRes = Result<Model, ModelLoaderError>;

        virtual TRes Load(const Path& path,
                          const ModelAssetOptions& options) const;
    };

}// namespace Nenuphar