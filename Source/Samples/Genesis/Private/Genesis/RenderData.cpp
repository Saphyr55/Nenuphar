#include "Genesis/RenderData.hpp"
#include "Genesis/Transform.hpp"
#include "Nenuphar/Asset/AssetRegistry.hpp"
#include "Nenuphar/Common/Debug/Debug.hpp"
#include "Nenuphar/Common/Instanciate.hpp"
#include "Nenuphar/Common/Type/Type.hpp"
#include "Nenuphar/Core/IO/Path.hpp"
#include "Nenuphar/Entity/Entity.hpp"
#include "Nenuphar/Entity/EntityRegistry.hpp"
#include "Nenuphar/Math/Vector4.hpp"
#include "Nenuphar/Model/Model.hpp"
#include "Nenuphar/Model/ModelLoader.hpp"
#include "Nenuphar/Model/TOL/TOLMeshLoader.hpp"
#include "Nenuphar/Rendering/OpenGL/OpenGLTexture.hpp"
#include "Nenuphar/Rendering/OpenGL/Uniform.hpp"
#include "Nenuphar/Rendering/RenderService.hpp"
#include "Nenuphar/Rendering/OpenGL/OpenGLRenderer.hpp"
#include "Nenuphar/Rendering/TextureAsset.hpp"
#include "glad/glad.h"

#include <optional>
#include <type_traits>


static Vector4f GDefaultColor =
        Vector4f(36.0f / 255.0f,
                 36.0f / 255.0f,
                 36.0f / 255.0f,
                 255.0f / 255.0f);


void OnRenderData(RenderData& data,
                  Np::EntityRegistry& registry,
                  Np::Entity floor,
                  Np::Entity bunny,
                  Np::Entity cube,
                  Np::Entity barrel)
{
    // We create the world model.
    Transform& transform = registry.GetComponent<Transform>(floor);
    Matrix4f floorModel = Transform::Tranformation(transform);

    Transform& cubeTransform = registry.GetComponent<Transform>(cube);
    Matrix4f cubeModel = Transform::Tranformation(cubeTransform);

    Transform& bunnyTransform = registry.GetComponent<Transform>(bunny);
    Matrix4f bunnyModel = Transform::Tranformation(bunnyTransform);

    Transform& barrelTransform = registry.GetComponent<Transform>(barrel);
    Matrix4f barrelModel = Transform::Tranformation(barrelTransform);

    Vector4f bunnyColor(0.95, 0.95, 0.95, 1);

    Vector4f floorColor(GDefaultColor);
    floorColor.w = GDefaultColor.x * 2;

    // We obtain uniforms from the register and indicate their respective values.
    // We draw the non textured models.
    // We draw the Bunny.
    data.Registry.Get<Bool>("UIsTextured").UpdateValue(false);
    data.Registry.Get<Vector4f>("UColor").UpdateValue(bunnyColor);
    data.Registry.Get<Matrix4f>("model").UpdateValue(bunnyModel);
    data.Renderer->DrawModel(*data.Shader, data.BunnyModelId);

    // We draw the Cube.
    data.Registry.Get<Matrix4f>("model").UpdateValue(cubeModel);
    data.Registry.Get<Bool>("UIsTextured").UpdateValue(true);
    data.Renderer->DrawModel(*data.Shader, data.CubeModelId);

    // We draw the Barrel.
    data.Registry.Get<Matrix4f>("model").UpdateValue(barrelModel);
    data.Registry.Get<Bool>("UIsTextured").UpdateValue(true);
    data.Renderer->DrawModel(*data.Shader, data.BarrelModelId);

    // We draw the Floor.
    data.Registry.Get<Bool>("UIsTextured").UpdateValue(false);
    data.Registry.Get<Matrix4f>("model").UpdateValue(floorModel);
    data.Registry.Get<Vector4f>("UColor").UpdateValue(floorColor);
    data.Renderer->DrawModel(*data.Shader, data.FloorModelId);
}


Np::SharedRef<RenderData> RenderData::Default()
{
    Np::RenderService::Instance()->Enable();
    Np::SharedRef<Np::Renderer> renderer = Np::RenderService::Instance()->GetRenderer();

    Np::TOLModelLoader modelLoader;

    Np::Path pathWall = Np::FromAssets("/Textures/Wall.jpg");
    Np::TextureAssetLoader textureAssetLoader;
    Np::SharedRef<Np::TextureAsset> assetWall = textureAssetLoader.Load(pathWall);
    CHECK(assetWall);
    Np::Texture wall = renderer->PersistTexture(assetWall);
    textureAssetLoader.Unload(assetWall);

    Np::Path bunnyPathObj = Np::FromAssets("/Models/bunny.obj");
    Np::ModelLoader::TRes bunnyRes = modelLoader.Load(bunnyPathObj);
    CHECK(bunnyRes.HasValue())
    Np::Model& bunnyModel = bunnyRes.Value();
    Np::ModelId bunnyModelId = renderer->PersistModel(bunnyModel);

    
    Np::Path cubePathObj = Np::FromAssets("/Models/Cube.obj");
    Np::ModelLoader::TRes cubeRes = modelLoader.Load(cubePathObj);
    CHECK(cubeRes.HasValue())
    Np::Model& cubeModel = cubeRes.Value();
    Np::ModelId cubeModelId = renderer->PersistModel(cubeModel);
    renderer->TextureModel(cubeModelId, wall);


    Np::Path barrelPathObj = Np::FromAssets("/Models/wine_barrel/wine_barrel_01_4k.obj");
    Np::Path mtlBarrelDirPath = Np::FromAssets("/Models/wine_barrel/");
    Np::ModelLoader::TRes barrelRes = modelLoader.Load(barrelPathObj, mtlBarrelDirPath);
    CHECK(barrelRes.HasValue())
    Np::Model& barrelModel = barrelRes.Value();
    Np::ModelId barrelModelId = renderer->PersistModel(barrelModel);

    
    Np::Model floorModel = Np::FloorModelFactory();
    Np::ModelId floorModelId = renderer->PersistModel(floorModel);

    
    Np::Path vertexFilepath = Np::FromAssets("/Shaders/MainVertex.glsl");
    Np::Path::TRes resultVertex = Np::ReadFileContent(vertexFilepath);
    CHECK(resultVertex.HasValue())
    
    Np::Path fragmentFilepath = Np::FromAssets("/Shaders/MainFragment.glsl");
    Np::Path::TRes resultFragment = Np::ReadFileContent(fragmentFilepath);
    CHECK(resultFragment.HasValue())

    auto program = MakeUnique<Np::OpenGLShader>(
            resultVertex.Value(),
            resultFragment.Value());

    Np::UniformRegistry registry(*program);
    registry
            .Register("UTex", 0)
            .Register("UColor", GDefaultColor)
            .Register("UIsTextured", false)
            .Register("proj", Matrix4f(1))
            .Register("view", Matrix4f(1))
            .Register("model", Matrix4f(1));

    return MakeSharedRef<RenderData>(
            bunnyModelId,
            floorModelId,
            cubeModelId,
            barrelModelId,
            wall,
            std::move(program),
            std::move(registry),
            renderer
    );
}