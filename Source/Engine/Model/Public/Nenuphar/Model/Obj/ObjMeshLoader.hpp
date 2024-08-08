#pragma once

#include "Nenuphar/Common/Type/Type.hpp"
#include "Nenuphar/Model/MeshLoader.hpp"

namespace Nenuphar
{

    class ObjMeshLoader : public MeshLoader
    {
    public:
        
        virtual SharedRef<Mesh> Load(const File& file);

        static UniquePtr<ObjMeshLoader> Create();

    };

}