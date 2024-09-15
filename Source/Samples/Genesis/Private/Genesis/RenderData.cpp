#include "Genesis/RenderData.hpp"
#include "Genesis/Transform.hpp"
#include "Nenuphar/Asset/AssetRegistry.hpp"
#include "Nenuphar/Core/Debug.hpp"
#include "Nenuphar/Common/Instanciate.hpp"
#include "Nenuphar/Common/Type/Type.hpp"
#include "Nenuphar/Core/IO/Path.hpp"
#include "Nenuphar/Entity/EntityRegistry.hpp"
#include "Nenuphar/Math/Vector4.hpp"
#include "Nenuphar/Model/Model.hpp"
#include "Nenuphar/Model/ModelAsset.hpp"
#include "Nenuphar/Rendering/OpenGL/Uniform.hpp"
#include "Nenuphar/Rendering/RenderService.hpp"
#include "Nenuphar/Rendering/Renderer.hpp"
#include "Nenuphar/Rendering/Texture.hpp"
#include "Nenuphar/Rendering/TextureAsset.hpp"

#include <optional>
#include <tuple>


void OnRenderData(RenderData& data, Np::EntityRegistry& registry)
{

    for (auto& [e, transform, rModel] : registry.View<Transform, RenderableModel>())
    {
        Matrix4f matrixModel = Transform::Tranformation(transform);
        
        data.Registry.Get<Matrix4f>("model").UpdateValue(matrixModel);

        data.Renderer->DrawModel(*data.Shader, data.Registry, rModel.Model);
    }
    /*
    for (auto& [e, transform, rModel, rTexture] : registry.View<Transform, RenderableModel, RenderableTexture>())
    {
        Matrix4f matrixModel = Transform::Tranformation(transform);

        data.Registry.Get<Matrix4f>("model").UpdateValue(matrixModel);
        data.Registry.Get<Bool>("UIsTextured").UpdateValue(true);

        data.Renderer->DrawModel(*data.Shader, rModel.Model);
    }
    
    for (auto& [e, transform, rModel, colorable] : registry.View<Transform, RenderableModel, Colorable>())
    {
        Matrix4f matrixModel = Transform::Tranformation(transform);

        data.Registry.Get<Bool>("UIsTextured").UpdateValue(false);
        data.Registry.Get<Vector4f>("UColor").UpdateValue(colorable.Color);
        data.Registry.Get<Matrix4f>("model").UpdateValue(matrixModel);

        data.Renderer->DrawModel(*data.Shader, rModel.Model);
    }
    */
}

RenderData::TRDefault RenderData::Default()
{
    // Use render singleton render service to get the main renderer,
    // and enable somes default graphics options.
    Np::RenderService::Instance()->Enable();
    
    Np::SharedRef<Np::Renderer> renderer =
            Np::RenderService::Instance()->GetRenderer();

    // Load a simple wall texture.
    Np::SharedRef<Np::TextureAsset> assetWall = Np::AssetRegistry::Instance()
            .Load<Np::TextureAsset>("/Textures/Wall.jpg");
    Np::Texture wall = renderer->PersistTexture(assetWall);

    // Load a simple cube as an obj model.
    Np::SharedRef<Np::ModelAsset> cubeAsset =Np::AssetRegistry::Instance()
            .Load<Np::ModelAsset>("/Models/Cube.obj");
    NCHECK(cubeAsset)
    Np::ModelId cubeModelId = renderer->PersistModel(cubeAsset->GetModel());
    renderer->TextureModel(cubeModelId, wall);

    // Load sponza obj model.
    Np::TOLModelAssetOptions sponzaOptions;
    sponzaOptions.PersistTexture = true;
    sponzaOptions.Renderer = renderer;
    sponzaOptions.MtlPathDir = Np::FromAssets("/sponza/");
    std::string path = "/sponza/sponza.obj";
    Np::SharedRef<Np::ModelAsset> sponzaAsset = Np::AssetRegistry::Instance()
            .Load<Np::ModelAsset, Np::ModelAssetOptions>(path, sponzaOptions);
    NCHECK(sponzaAsset)
    Np::ModelId sponzaModelId = renderer->PersistModel(sponzaAsset->GetModel());

    // Create floor model.
    Np::Model floorModel = Np::FloorModelFactory();
    Np::ModelId floorModelId = renderer->PersistModel(floorModel);

    // Load the vertex shader.
    Np::Path vertexFilepath = Np::FromAssets("/Shaders/MainVertex.glsl");
    Np::Path::TRes resultVertex = Np::ReadFileContent(vertexFilepath);
    NCHECK(resultVertex.HasValue())

    // Load the fragment shader.
    Np::Path fragmentFilepath = Np::FromAssets("/Shaders/MainFragment.glsl");
    Np::Path::TRes resultFragment = Np::ReadFileContent(fragmentFilepath);
    NCHECK(resultFragment.HasValue())

    // Create the main OpenGL shader.
    auto program = MakeUnique<Np::OpenGLShader>(resultVertex.Value(),
                                                resultFragment.Value());

    // TODO: Replace to an uniform buffer.
    Np::UniformRegistry registry(*program);
    registry.Register("UTex", 0)
            .Register("UColor", GDefaultColor)
            .Register("UIsTextured", false)
            .Register("proj", Matrix4f(1))
            .Register("view", Matrix4f(1))
            .Register("model", Matrix4f(1));

    auto data = MakeSharedRef<RenderData>(std::move(program),
                                     std::move(registry), 
                                     renderer);

    return std::make_tuple(data, 
        RenderModels(cubeModelId, sponzaModelId, floorModelId), 
        RenderTextures(wall));
}