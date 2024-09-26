#include "Genesis/RenderData.hpp"
#include "Genesis/Transform.hpp"
#include "Nenuphar/Asset/AssetRegistry.hpp"
#include "Nenuphar/Common/Type/Type.hpp"
#include "Nenuphar/Core/Debug.hpp"
#include "Nenuphar/Entity/EntityRegistry.hpp"
#include "Nenuphar/Math/Matrix4.hpp"
#include "Nenuphar/Math/Vector3.hpp"
#include "Nenuphar/Model/Model.hpp"
#include "Nenuphar/Model/ModelAsset.hpp"
#include "Nenuphar/RenderLight/RenderTypes.hpp"

#include "Nenuphar/Rendering/CommandBuffer.hpp"
#include "Nenuphar/Rendering/RenderDevice.hpp"
#include "Nenuphar/Rendering/Shader.hpp"
#include "Nenuphar/Rendering/UniformRegistry.hpp"

#include <memory>


void RenderData::OnRenderData(SharedRef<Np::CommandBuffer> commandBuffer, Np::EntityRegistry& registry)
{
    SharedRef<Np::MainShaderProgram> shader = Device->GetMainShaderProgram();

    for (auto& [e, transform, rModel]: registry.View<Transform, RenderableModel>())
    {
        Matrix4f matrixModel = Transform::Tranformation(transform);

        commandBuffer->Record([=] {
            shader->GetRegistry()->Get<Matrix4f>("UModel").UpdateValue(matrixModel);
        });

        RenderCommandDrawModel(commandBuffer, shader->GetRegistry(), *rModel.Model);
    }
    
    for (auto& [e, light, transform, rModel]: registry.View<Np::Light, Transform, RenderableModel>())
    {
        Matrix4f matrixModel = Transform::Tranformation(transform);

        commandBuffer->Record([=] {
            shader->GetRegistry()->Get<Matrix4f>("UModel").UpdateValue(matrixModel);
            shader->GetRegistry()->Get<Vector3f>("ULight.Position").UpdateValue(light.Position);
            shader->GetRegistry()->Get<Vector3f>("ULight.Ambient").UpdateValue(light.Ambient);
            shader->GetRegistry()->Get<Vector3f>("ULight.Diffuse").UpdateValue(light.Diffuse);
            shader->GetRegistry()->Get<Vector3f>("ULight.Specular").UpdateValue(light.Specular);
        });

        RenderCommandDrawModel(commandBuffer, shader->GetRegistry(), *rModel.Model);
    }
    
}

RenderData RenderData::Create(SharedRef<RenderDevice> device)
{
    // Use render device to enable somes default graphics option.
    device->Enable();

    // Use render device to get the main shader program.
    Np::SharedRef<Np::MainShaderProgram> shader = device->GetMainShaderProgram();

    // Get the singleton asset registry.
    Np::AssetRegistry& assets = Np::AssetRegistry::Instance();

    // Load sponza obj model.
    Np::TOLModelAssetOptions sponzaOptions;
    sponzaOptions.RenderDevice = device;
    sponzaOptions.MtlPathDir = Np::FromAssets("/sponza/");
    std::string path = "/sponza/sponza.obj";
    Np::ModelAssetRef sponzaAsset = assets.Load<Np::ModelAsset, Np::TOLModelAssetOptions>(path, sponzaOptions);
    NCHECK(sponzaAsset)

    RenderData data;
    data.SponzaAsset = sponzaAsset;
    data.Device = device;

    return std::move(data);
}