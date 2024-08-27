#pragma once

#include "Nenuphar/Common/Type/Type.hpp"
#include "Nenuphar/Model/ModelLoader.hpp"

#include <optional>

namespace Nenuphar
{

    class ObjModelLoader : public ModelLoader
    {
    public:
        virtual TRes Load(const Path& path,
                          std::optional<Path> mtlPathDir = std::nullopt) const override;

        static UniquePtr<ObjModelLoader> Create();

    };

}