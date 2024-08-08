#pragma once

#include "Nenuphar/Common/Type/Type.hpp"
#include "Nenuphar/Model/Obj/ObjMeshLoader.hpp"

namespace Nenuphar
{
    
    class ObjMeshLoaderImpl : public ObjMeshLoader
    {
    public:
        SharedRef<Mesh> Load(const File& file) override;
    };

}