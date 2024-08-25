#pragma once

#include "Nenuphar/Core/IO/Path.hpp"
#include "Nenuphar/Model/ModelLoader.hpp"


namespace Nenuphar
{

    class TOLModelLoader : public ModelLoader
    {
    public:
        virtual Result<Model, ModelLoaderError> Load(const Path& path) const override;
    };
    
}