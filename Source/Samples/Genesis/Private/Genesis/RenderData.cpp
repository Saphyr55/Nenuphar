#include "Genesis/RenderData.hpp"
#include "Genesis/Transform.hpp"
#include "Nenuphar/Asset/AssetRegistry.hpp"
#include "Nenuphar/Common/Instanciate.hpp"
#include "Nenuphar/Common/Type/Type.hpp"
#include "Nenuphar/Core/Debug.hpp"
#include "Nenuphar/Core/IO/Path.hpp"
#include "Nenuphar/Entity/EntityRegistry.hpp"
#include "Nenuphar/Math/Vector3.hpp"
#include "Nenuphar/Math/Vector4.hpp"
#include "Nenuphar/Model/Model.hpp"
#include "Nenuphar/Model/ModelAsset.hpp"
#include "Nenuphar/RenderLight/RenderTypes.hpp"
#include "Nenuphar/Rendering/OpenGL/Uniform.hpp"
#include "Nenuphar/Rendering/RenderService.hpp"
#include "Nenuphar/Rendering/Renderer.hpp"


#include <optional>
#include <tuple>


void OnRenderData(RenderData& data, Np::EntityRegistry& registry)
{
    for (auto& [e, transform, rModel]: registry.View<Transform, RenderableModel>())
    {
        Matrix4f matrixModel = Transform::Tranformation(transform);

        data.MaterialRegistry.Get<Matrix4f>("model").UpdateValue(matrixModel);
        data.Renderer->DrawModel(*data.MaterialShader, data.MaterialRegistry, rModel.Model);
    }
}

RenderData::TRDefault RenderData::Default()
{
    // Use render singleton render service to get the main renderer,
    // and enable somes default graphics options.
    Np::RenderService::Instance()->Enable();

    Np::SharedRef<Np::Renderer> renderer =
            Np::RenderService::Instance()->GetRenderer();

    // Load the wine barrel model asset.
    Np::TOLModelAssetOptions barrelOptions;
    barrelOptions.PersistTexture = true;
    barrelOptions.Renderer = renderer;
    barrelOptions.MtlPathDir = Np::FromAssets("/Models/wine_barrel/");
    Np::SharedRef<Np::ModelAsset> barrelAsset = 
        Np::AssetRegistry::Instance().Load<Np::ModelAsset>("/Models/wine_barrel/wine_barrel_01_4k.obj", barrelOptions);
    NCHECK(barrelAsset)
    Np::ModelId barrelModelId = renderer->PersistModel(barrelAsset->GetModel());

    // Load sponza obj model.
    Np::TOLModelAssetOptions sponzaOptions;
    sponzaOptions.PersistTexture = true;
    sponzaOptions.Renderer = renderer;
    sponzaOptions.MtlPathDir = Np::FromAssets("/sponza/");
    std::string path = "/sponza/sponza.obj";
    Np::SharedRef<Np::ModelAsset> sponzaAsset = 
        Np::AssetRegistry::Instance().Load<Np::ModelAsset, Np::ModelAssetOptions>(path, sponzaOptions);
    NCHECK(sponzaAsset)
    Np::ModelId sponzaModelId = renderer->PersistModel(sponzaAsset->GetModel());

    // Create floor model.
    Np::Model floorModel = Np::FloorModelFactory();
    Np::ModelId floorModelId = renderer->PersistModel(floorModel);

    // Load the material vertex shader.
    Np::Path materialVertexFilepath = Np::FromAssets("/Shaders/MaterialVertex.glsl");
    Np::Path::TRes resultMaterialVertex = Np::ReadFileContent(materialVertexFilepath);
    NCHECK(resultMaterialVertex.HasValue())

    // Load the material fragment shader.
    Np::Path materialFragmentFilepath = Np::FromAssets("/Shaders/MaterialFragment.glsl");
    Np::Path::TRes resultMaterialFragment = Np::ReadFileContent(materialFragmentFilepath);
    NCHECK(resultMaterialFragment.HasValue())

    // Create the main OpenGL shader.
    auto materialProgram = MakeUnique<Np::OpenGLShader>(resultMaterialVertex.Value(), resultMaterialFragment.Value());

    // TODO: Replace to an uniform buffer.
    Np::UniformRegistry materialRegistry(*materialProgram);
    materialRegistry
            .Register("UTexture", Int(0))

            .Register("UCameraPosition", Vector3f(0.0f))

            .Register("UDirectionalLight.Position", Vector3f(1.0f))
            .Register("UDirectionalLight.Ambient", Vector3f(0.8f))
            .Register("UDirectionalLight.Diffuse", Vector3f(0.5f))
            .Register("UDirectionalLight.Specular", Vector3f(1.0f))

            .Register("UMaterial.Diffuse", Vector3f(0.5f))
            .Register("UMaterial.Specular", Vector3f(1.0f))
            .Register("UMaterial.Shininess", 2.0f)
            .Register("UMaterial.SpecularTexture", Int(0))
            .Register("UMaterial.DiffuseTexture", Int(0))

            .Register("proj", Matrix4f(1))
            .Register("view", Matrix4f(1))
            .Register("model", Matrix4f(1));

    auto data = MakeSharedRef<RenderData>(
            std::move(materialProgram),
            std::move(materialRegistry),
            renderer);

    return std::make_tuple(data, RenderModels(barrelModelId, sponzaModelId, floorModelId));
}