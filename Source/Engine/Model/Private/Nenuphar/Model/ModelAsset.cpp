#include "Nenuphar/Model/ModelAsset.hpp"

#include "Nenuphar/Common/Type/Type.hpp"
#include "Nenuphar/Core/Debug.hpp"
#include "Nenuphar/Common/Instanciate.hpp"
#include "Nenuphar/Core/Logger/Logger.hpp"
#include "Nenuphar/Model/ModelLoader.hpp"
#include "Nenuphar/Model/TOL/TOLMeshLoader.hpp"


namespace Nenuphar
{

    ModelAssetLoader::ModelAssetLoader() 
        : m_objLoader(MakeSharedRef<TOLModelLoader>())
    {

    }

    ModelAsset::ModelAsset(Model&& model)
        : m_model(model)
    {
    }

    SharedRef<ModelAsset> ModelAssetLoader::Load(const Path& path,
                                                 const ModelAssetOptions& options)
    {
        const ModelAssetOptions* optionsPtr = &options;
        if (path.GetExtenstion() == ".obj")
        {
            // TODO: Better way to get the options.
            const TOLModelAssetOptions* tolOptions = 
                static_cast<const TOLModelAssetOptions*>(optionsPtr);

            ModelLoader::TRes res = m_objLoader->Load(path, *tolOptions);
            
            if (!res.HasValue())
            {
                return nullptr;
            }

            return MakeSharedRef<ModelAsset>(std::move(res.Value()));
        }
        else
        {
            NP_ERROR(ModelAssetLoader::Load,
                     "No loader found for this format : '{}'.", path.GetExtenstion());
            NCHECK(false)
        }

        return nullptr;
    }


    void ModelAssetLoader::Unload(SharedRef<ModelAsset> asset)
    {
    }
    
}// namespace Nenuphar