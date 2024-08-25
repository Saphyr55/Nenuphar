#include "Nenuphar/Model/Obj/ObjMeshLoader.hpp"

namespace Nenuphar
{

    Result<Model, ModelLoaderError> ObjModelLoader::Load(const Path& path) const
    {
        using Res = Result<Model, ModelLoaderError>;
        return Res(Res::kErrTag, ModelLoaderError::MalFormat);
    }
    
}