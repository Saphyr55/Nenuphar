#pragma once

#include "Nenuphar/Common/Common.hpp"
#include "Nenuphar/Core/Resource/Resource.hpp"

#include <tuple>

namespace Nenuphar
{

    class Mesh;

    enum class MeshLoaderError
    {

    };
    
    class MeshLoader
    {
    public:
        virtual SharedRef<Mesh> Load(const File& path) = 0;
    };

}