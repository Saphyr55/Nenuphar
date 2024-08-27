#include "Genesis/RenderData.hpp"
#include "Genesis/Transform.hpp"
#include "Nenuphar/Common/Debug/Debug.hpp"
#include "Nenuphar/Common/Instanciate.hpp"
#include "Nenuphar/Entity/Entity.hpp"
#include "Nenuphar/Entity/EntityRegistry.hpp"
#include "Nenuphar/Math/Vector4.hpp"
#include "Nenuphar/Model/Model.hpp"
#include "Nenuphar/Model/TOL/TOLMeshLoader.hpp"
#include "Nenuphar/Rendering/OpenGL/OpenGLTexture.hpp"
#include "Nenuphar/Rendering/OpenGL/Uniform.hpp"
#include "Nenuphar/Rendering/RenderSystem.hpp"
#include "Nenuphar/Rendering/OpenGL/OpenGLRenderer.hpp"

static Vector4f GDefaultColor =
        Vector4f(36.0f / 255.0f,
                 36.0f / 255.0f,
                 36.0f / 255.0f,
                 255.0f / 255.0f);

void OnRenderData(RenderData& data,
                  Np::EntityRegistry& registry,
                  Np::Entity floor,
                  Np::Entity bunny,
                  Np::Entity cube)
{
    // We create the world model.
    Transform& transform = registry.GetComponent<Transform>(floor);
    Matrix4f floorModel = Transform::Tranformation(transform);

    Transform& cubeTransform = registry.GetComponent<Transform>(cube);
    Matrix4f cubeModel = Transform::Tranformation(cubeTransform);

    Transform& bunnyTransform = registry.GetComponent<Transform>(bunny);
    Matrix4f bunnyModel = Transform::Tranformation(bunnyTransform);

    Vector4f bunnyColor(0.95, 0.95, 0.95, 1);

    Vector4f floorColor(GDefaultColor);
    floorColor.w = GDefaultColor.x * 2;

    // We obtain uniforms from the register and indicate their respective values.
    // We draw the non textured models.
    // We draw the Bunny.
    data.Registry->Get<Bool>("UIsTextured").UpdateValue(false);
    data.Registry->Get<Vector4f>("UColor").UpdateValue(bunnyColor);
    data.Registry->Get<Matrix4f>("model").UpdateValue(bunnyModel);
    data.Renderer->DrawModel(*data.Shader, data.BunnyModelId);

    // We draw the Cube.
    data.Registry->Get<Matrix4f>("model").UpdateValue(cubeModel);
    data.Registry->Get<Bool>("UIsTextured").UpdateValue(true);
    data.Renderer->DrawModel(*data.Shader, data.CubeModelId);

    // We draw the Floor.
    data.Registry->Get<Bool>("UIsTextured").UpdateValue(false);
    data.Registry->Get<Matrix4f>("model").UpdateValue(floorModel);
    data.Registry->Get<Vector4f>("UColor").UpdateValue(floorColor);
    data.Renderer->DrawModel(*data.Shader, data.FloorModelId);
}


SharedRef<RenderData> RenderData::Default()
{
    Np::RenderSystem::Instance().Enable();

    TOLModelLoader modelLoader;

    auto renderer = MakeUnique<Np::OpenGLRenderer>();

    Path pathWall = Np::FromAssets("/Textures/Wall.jpg");
    Np::SharedRef<OpenGLTexture2D> wall =
            Np::OpenGLTexture2D::LoadFromImage(pathWall, &DefaultParameterTexture);

    Path bunnyPathObj = Np::FromAssets("/Models/bunny.obj");
    auto bunnyRes = modelLoader.Load(bunnyPathObj);
    CHECK(bunnyRes.HasValue())

    Path cubePathObj = Np::FromAssets("/Models/Cube.obj");
    auto cubeRes = modelLoader.Load(cubePathObj);
    CHECK(cubeRes.HasValue())

    Model& bunnyModel = bunnyRes.Value();
    Model& cubeModel = cubeRes.Value();
    Model floorModel = Np::FloorModelFactory();

    ModelId bunnyModelId = renderer->PersistModel(bunnyModel);
    ModelId cubeModelId  = renderer->PersistModel(cubeModel);
    ModelId floorModelId = renderer->PersistModel(floorModel);

    renderer->TextureModel(cubeModelId, wall->GetHandle());

    Path vertexFilepath   = Np::FromAssets("/Shaders/MainVertex.glsl");
    Path fragmentFilepath = Np::FromAssets("/Shaders/MainFragment.glsl");

    Path::TRes resultVertex   = Np::ReadFileContent(vertexFilepath);
    CHECK(resultVertex.HasValue())

    Path::TRes resultFragment = Np::ReadFileContent(fragmentFilepath);
    CHECK(resultFragment.HasValue())

    auto program = MakeUnique<Np::OpenGLShader>(
            resultVertex.Value(),
            resultFragment.Value());
    
    auto registry = MakeUnique<Np::UniformRegistry>(*program);
    registry
            ->Register("UTex", 0)
            .Register("UColor", GDefaultColor)
            .Register("UIsTextured", false)
            .Register("proj", Matrix4f(1))
            .Register("view", Matrix4f(1))
            .Register("model", Matrix4f(1));

    return MakeSharedRef<RenderData>(
            bunnyModelId,
            floorModelId,
            cubeModelId,
            wall,
            std::move(program),
            std::move(registry),
            std::move(renderer)
    );
}