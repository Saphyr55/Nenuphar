#include "Genesis/Genesis.hpp"
#include "Nenuphar/Assets/Assets.hpp"
#include "Nenuphar/Graphics/OpenGL/OpenGLVertexArray.hpp"
#include "Nenuphar/Graphics/OpenGL/Texture.hpp"
#include "Nenuphar/Graphics/OpenGL/Shader.hpp"
#include "Nenuphar/Graphics/OpenGL/Uniform.hpp"

#include <glad/glad.h>

using namespace Nenuphar;

Env::Env(UInt16 id, Ptr<GraphicContext> graphicContext, Window& window)
        : Id(id)
        , MainGraphicContext(std::move(graphicContext))
        , MainWindow(window)
        , MainCamera(Radians(45.f),
                     Radians(45.0f),
                     3,
                     Vector3f(0.0, 0.0, 0.0),
                     Vector3f(0.0f, 1.0f, 0.0f))
{
}

void UpdatePVM(UniformRegistry& registry, const OrbitCamera& camera, const Window& w)
{
    // We obtain a projection matrix using the perspective matrix with a fov of 45 degrees,
    // the window aspect, and 0.1 close up and 100 far away.
    Matrix4f proj  = Matrix4f::Perspective(Radians(45), (Float) w.Width / w.Height, 0.1f, 100.0f);

    // We obtain the view in function of the camera.
    Matrix4f view  = Matrix4f::LookAt(camera.Position(), camera.Target, camera.Up);

    // We create the world model.
    Matrix4f model = Matrix4f::Identity(); //Matrix4f::Rotate(Matrix4f(1), Oc::Radians(90), { 0.5f, 1.0f, 0.0f });

    // We obtain uniforms from the register and indicate their respective values.
    registry.Get<Matrix4f>("proj").UpdateValue(proj);
    registry.Get<Matrix4f>("model").UpdateValue(model);
    registry.Get<Matrix4f>("view").UpdateValue(view);
}


void Env::Init(Env& env)
{

    auto& window = env.MainWindow;
    auto& windowSignals = window.GetWindowSignals();

    windowSignals.OnClose().Connect(
            [&](auto&, auto&)
            {
                window.Destroy();
                GIsFinish = true;
            });

    windowSignals.OnResize().ConnectHandler(
            [&](auto&)
            {
                Render(env);
            });

    window.Show();

    glEnable(GL_DEPTH_TEST);
    OpenGLVertexArray vao;
    OpenGLVertexBuffer vbo(Cube);

    LinkBuffer(vbo, {
            { 0, 3, GL_FLOAT, sizeof(Vertex), nullptr },
            { 1, 2, GL_FLOAT, sizeof(Vertex), (VoidPtr)(3 * sizeof(Float)) },
    });

    OpenGLTexture2D wall = OpenGLTexture2D::LoadFromImage(
            AssetsFolder::Path("Assets/Textures/Wall.jpg"),
            &DefaultParameterTexture);

    String vertexFilepath = AssetsFolder::Path("/Shaders/MainVertex.glsl");
    String fragmentFilepath = AssetsFolder::Path("/Shaders/MainFragment.glsl");
    OpenGLShader program(vertexFilepath, fragmentFilepath);

    UniformRegistry registry(program);
    { registry
                .Register("tex1", UInt32(wall))
                .Register("proj", Matrix4f(1))
                .Register("view", Matrix4f(1))
                .Register("model", Matrix4f(1));
    }

}

void Env::Render(Env& env)
{
    glClearColor(0.2, 0.2, 0.4, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    env.MainGraphicContext->SwapBuffers();
    env.MainWindow.PoolEvent();
}

Env& Env::New(Window& window)
{
    static UInt16 index = 0;
    EnvRegistry.insert({
        ++index,
        MakeUnique<Env>(
                index,
                GraphicContext::Create(window),
                window)
    });
    return *EnvRegistry[index];
}

