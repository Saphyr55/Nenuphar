#include "Nenuphar/Model/Obj/ObjMeshLoader.hpp"

namespace Nenuphar
{

    ModelLoader::TRes ObjModelLoader::Load(const Path& path,
                                           std::optional<Path> mtlPathDir) const
    {
        using Res = ModelLoader::TRes;
        return Res(Res::kErrTag, ModelLoaderError::MalFormat);
    }
    
}