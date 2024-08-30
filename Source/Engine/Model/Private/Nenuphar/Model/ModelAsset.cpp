#include "Nenuphar/Model/ModelAsset.hpp"

#include "Nenuphar/Core/Debug.hpp"
#include "Nenuphar/Common/Instanciate.hpp"
#include "Nenuphar/Core/Logger/Logger.hpp"
#include "Nenuphar/Model/ModelLoader.hpp"


namespace Nenuphar
{



    ModelAsset::ModelAsset(Model&& model)
        : m_model(model)
    {
    }


    SharedRef<ModelAsset> ModelAssetLoader::Load(const Path& path,
                                                 const ModelAssetOptions& options)
    {
        ModelLoader* loader = nullptr;
        if (path.GetExtenstion() == ".obj")
        {
            loader = &m_objLoader;
        }
        else
        {
            NP_ERROR(ModelAssetLoader::Load,
                     "No loader found for this format : '{}'.", path.GetExtenstion());
            NCHECK(loader)
        }

        ModelLoader::TRes res = loader->Load(path, options.MtlPathDir);

        if (!res.HasValue())
        {
            return nullptr;
        }

        return MakeSharedRef<ModelAsset>(std::move(res.Value()));
    }


    void ModelAssetLoader::Unload(SharedRef<ModelAsset> asset)
    {
    }
    
}// namespace Nenuphar