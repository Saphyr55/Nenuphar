#pragma once

#include "Nenuphar/Common/Type/Type.hpp"
#include "Nenuphar/MeshLoader/MeshLoader.hpp"

namespace Nenuphar
{

    class ObjMeshLoader : public MeshLoader
    {
    public:
        SharedRef<Mesh> Load(const File& file) override;
        
    private:
    };

}