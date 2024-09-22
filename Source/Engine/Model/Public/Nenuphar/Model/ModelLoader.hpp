#pragma once

#include "Nenuphar/Common/Type/Result.hpp"
#include "Nenuphar/Core/IO/Path.hpp"
#include "Nenuphar/Model/Model.hpp"
#include "Nenuphar/Model/ModelAsset.hpp"


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