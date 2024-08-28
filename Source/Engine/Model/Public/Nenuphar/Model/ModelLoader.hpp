#pragma once

#include "Nenuphar/Asset/Asset.hpp"
#include "Nenuphar/Common/Type/Result.hpp"
#include "Nenuphar/Core/IO/Path.hpp"
#include "Nenuphar/Model/Model.hpp"


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

    public :
        virtual TRes Load(const Path& path,
                          std::optional<Path> mtlPathDir = std::nullopt) const = 0;
    };

}