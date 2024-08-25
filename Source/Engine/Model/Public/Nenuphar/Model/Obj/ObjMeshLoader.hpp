#pragma once

#include "Nenuphar/Common/Type/Type.hpp"
#include "Nenuphar/Model/ModelLoader.hpp"

#include <optional>

namespace Nenuphar
{

    class ObjModelLoader : public ModelLoader
    {
    public:
        Result<Model, ModelLoaderError> Load(const Path& path) const override;

        static UniquePtr<ObjModelLoader> Create();

    };

}