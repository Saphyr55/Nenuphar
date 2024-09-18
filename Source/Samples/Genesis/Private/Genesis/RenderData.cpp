#include "Genesis/RenderData.hpp"
#include "Genesis/Transform.hpp"
#include "Nenuphar/Asset/AssetRegistry.hpp"
#include "Nenuphar/Common/Instanciate.hpp"
#include "Nenuphar/Common/Type/Type.hpp"
#include "Nenuphar/Core/Debug.hpp"
#include "Nenuphar/Entity/EntityRegistry.hpp"
#include "Nenuphar/Math/Matrix4.hpp"
#include "Nenuphar/Math/Vector3.hpp"
#include "Nenuphar/Model/Model.hpp"
#include "Nenuphar/Model/ModelAsset.hpp"
#include "Nenuphar/RenderLight/RenderTypes.hpp"
#include "Nenuphar/Rendering/RenderService.hpp"
#include "Nenuphar/Rendering/Renderer.hpp"
#include "Nenuphar/Rendering/Shader.hpp"
#include "Nenuphar/Rendering/Uniform.hpp"

#include <memory>


void RenderData::OnRenderData(Np::EntityRegistry& registry)
{
    SharedRef<Np::Renderer> renderer = Np::RenderService::Instance()->GetRenderer(); 
    SharedRef<MainShaderProgram> shader = renderer->GetMainShaderProgram();
    
    for (auto& [e, transform, rModel]: registry.View<Transform, RenderableModel>())
    {
        Matrix4f matrixModel = Transform::Tranformation(transform);
        shader->GetRegistry()->Get<Matrix4f>("UModel").UpdateValue(matrixModel);
        renderer->DrawModel(shader->GetDelegate(), shader->GetRegistry(), rModel.Model);
    }

    for (auto& [e, light, transform, rModel]: registry.View<Np::Light, Transform, RenderableModel>())
    {
        Matrix4f matrixModel = Transform::Tranformation(transform);

        shader->GetRegistry()->Get<Matrix4f>("UModel").UpdateValue(matrixModel);
        shader->GetRegistry()->Get<Vector3f>("ULight.Position").UpdateValue(light.Position);
        shader->GetRegistry()->Get<Vector3f>("ULight.Ambient").UpdateValue(light.Ambient);
        shader->GetRegistry()->Get<Vector3f>("ULight.Diffuse").UpdateValue(light.Diffuse);
        shader->GetRegistry()->Get<Vector3f>("ULight.Specular").UpdateValue(light.Specular);

        renderer->DrawModel(shader->GetDelegate(), shader->GetRegistry(), rModel.Model);
    }
}

RenderData RenderData::Create()
{
    // Use render singleton render service to get the main renderer,
    // and enable somes default graphics options.
    Np::RenderService::Instance()->Enable();

    Np::SharedRef<Np::Renderer> renderer =
            Np::RenderService::Instance()->GetRenderer();

    Np::SharedRef<Np::MainShaderProgram> shader = renderer->GetMainShaderProgram();

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

    return RenderData(barrelModelId, sponzaModelId, floorModelId);
}