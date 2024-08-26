#include "Genesis/RenderData.hpp"
#include "Nenuphar/Common/Instanciate.hpp"
#include "Nenuphar/Model/Model.hpp"
#include "Nenuphar/Model/TOL/TOLMeshLoader.hpp"
#include "Nenuphar/Rendering/RenderSystem.hpp"
#include "Nenuphar/Rendering/OpenGL/OpenGLRenderer.hpp"

void OnRenderData(RenderData& data)
{
    // We bind the texture for the Cube.
    Np::ActiveTexture(0);
    data.WallTexture.Bind();

    // We draw the Cube.
    data.Renderer->DrawModel(*data.Shader, data.Model);
}

SharedRef<RenderData> RenderData::Default()
{
    Np::RenderSystem::Instance().Enable();

    auto renderer = MakeUnique<Np::OpenGLRenderer>();

    auto cubePathObj = Np::FromAssets("/Models/Cube.obj");
    auto pathWall = Np::FromAssets("/Textures/Wall.jpg");
    auto wall = Np::OpenGLTexture2D::LoadFromImage(pathWall, &DefaultParameterTexture);

    TOLModelLoader modelLoader;
    auto res = modelLoader.Load(cubePathObj);
    if (!res.HasValue())
    {
        return nullptr;
    }
    
    auto model = res.Value();
    auto modelId = renderer->PersistModel(FloorModel);
    
    auto mesh = FloorModel.Meshes[0];
    mesh->Textures.push_back(Texture(wall));

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
    registry->Register("tex1",  (Int) Texture(wall))
            .Register("proj", Matrix4f(1))
            .Register("view", Matrix4f(1))
            .Register("model", Matrix4f(1));

    return MakeSharedRef<RenderData>(
            modelId,
            wall,
            std::move(program),
            std::move(registry),
            std::move(renderer));
}