#include "Genesis/RenderData.hpp"
#include "Nenuphar/Common/Instanciate.hpp"
#include "Nenuphar/Math/Vector4.hpp"
#include "Nenuphar/Model/Model.hpp"
#include "Nenuphar/Model/TOL/TOLMeshLoader.hpp"
#include "Nenuphar/Rendering/OpenGL/OpenGLTexture.hpp"
#include "Nenuphar/Rendering/OpenGL/Uniform.hpp"
#include "Nenuphar/Rendering/RenderSystem.hpp"
#include "Nenuphar/Rendering/OpenGL/OpenGLRenderer.hpp"
#include "Nenuphar/Rendering/Texture.hpp"

void OnRenderData(RenderData& data)
{
    // We draw the Cube.
    data.Registry->Get<Bool>("UIsTextured").UpdateValue(false);
    data.Renderer->DrawModel(*data.Shader, data.CubeModelId);

    // We draw the Floor.
    data.Registry->Get<Bool>("UIsTextured").UpdateValue(true);
    data.Renderer->DrawModel(*data.Shader, data.FloorModelId);
}

SharedRef<RenderData> RenderData::Default()
{
    Np::RenderSystem::Instance().Enable();

    auto renderer = MakeUnique<Np::OpenGLRenderer>();

    auto pathWall = Np::FromAssets("/Textures/Wall.jpg");
    auto wall = Np::OpenGLTexture2D::LoadFromImage(pathWall, &DefaultParameterTexture);

    // auto cubePathObj = Np::FromAssets("/Models/House/house.obj");
    // TOLModelLoader modelLoader;
    // auto res = modelLoader.Load(cubePathObj);
    // if (!res.HasValue())
    // {
    //     return nullptr;
    // }

    // auto& houseModel = res.Value();

    auto cubeModel = Np::CubeModelFactory();
    auto floorModel = Np::FloorModelFactory();
    
    auto cubeModelId = renderer->PersistModel(cubeModel);
    auto floorModelId = renderer->PersistModel(floorModel);
    
    renderer->TextureModel(floorModelId, wall->GetHandle());

    auto vertexFilepath = Np::FromAssets("/Shaders/MainVertex.glsl");
    auto fragmentFilepath = Np::FromAssets("/Shaders/MainFragment.glsl");

    auto resultVertex = Np::ReadFileContent(vertexFilepath);
    auto resultFragment = Np::ReadFileContent(fragmentFilepath);

    if (!resultVertex.HasValue())
    {
        return nullptr;
    }

    if (!resultFragment.HasValue())
    {
        return nullptr;
    }

    auto program = MakeUnique<Np::OpenGLShader>(
            resultVertex.Value(),
            resultFragment.Value());

    auto registry = MakeUnique<Np::UniformRegistry>(*program);
    registry
            ->Register("UTex", 0)
            .Register("UColor", Vector4f(1.00f, 0.65f, 0.00f, 1.00f))
            .Register("UIsTextured", true)
            .Register("proj", Matrix4f(1))
            .Register("view", Matrix4f(1))
            .Register("model", Matrix4f(1));

    return MakeSharedRef<RenderData>(
            floorModelId,
            cubeModelId,
            wall,
            std::move(program),
            std::move(registry),
            std::move(renderer)
    );
}