#pragma once

#include "Nenuphar/Core/IO/Path.hpp"
#include "Nenuphar/Model/ModelLoader.hpp"


namespace Nenuphar
{

    class TOLModelLoader : public ModelLoader
    {
    public:
        virtual ModelLoader::TRes Load(const Path& path,
                                       std::optional<Path> mtlPathDir = std::nullopt
                                               ) const override;
    };
    
}