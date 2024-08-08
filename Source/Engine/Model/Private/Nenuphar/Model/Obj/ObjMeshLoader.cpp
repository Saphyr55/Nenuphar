#include "Nenuphar/Model/Obj/ObjMeshLoader.hpp"
#include "Nenuphar/Common/Instanciate.hpp"

#include "ObjMeshLoaderImpl.hpp"

namespace Nenuphar
{

    static UniquePtr<ObjMeshLoader> Create()
    {
        return MakeUnique<ObjMeshLoaderImpl>();    
    }

    SharedRef<Mesh> ObjMeshLoader::Load(const File& file)
    {
        return nullptr;    
    }
}