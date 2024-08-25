#pragma once

#include "Nenuphar/Common/Type/Result.hpp"
#include "Nenuphar/Core/Resource/Resource.hpp"
#include "Nenuphar/Model/Model.hpp"

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
        virtual Result<Model, ModelLoaderError> Load(const Path& path) const = 0;
    };

}