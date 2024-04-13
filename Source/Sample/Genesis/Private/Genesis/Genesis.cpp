#include "Genesis/Genesis.hpp"
#include "Nenuphar/InputSystem/InputSystem.hpp"

#include <glad/glad.h>

using namespace Nenuphar;

Env::Env(UInt16 id, Ptr<GraphicContext> graphicContext, Window& window)
        : Id(id)
        , MainGraphicContext(std::move(graphicContext))
        , MainWindow(window)
        , MainRenderer(Renderer::New())
        , MainCamera((Float) Radians(45.0f),
                     (Float) Radians(45.0f),
                     3.0f,
                     Vector3f(0.0, 0.0, 0.0),
                     Vector3f(0.0f, 1.0f, 0.0f))
{
}

void UpdatePVM(UniformRegistry& registry, const OrbitCamera& camera, const Window& window)
{

    Float width = window.GetWindowDefinition().Width;
    Float height = window.GetWindowDefinition().Height;

    // We obtain a projection matrix using the perspective matrix with a fov of 45 degrees,
    // the window aspect, and 0.1 close up and 100 far away.
    Matrix4f proj  = Matrix4f::Perspective(Radians(45), (Float) width / height, 0.1f, 100.0f);

    // We obtain the view in function of the camera.
    Matrix4f view  = Matrix4f::LookAt(camera.Position(), camera.Target, camera.Up);

    // We create the world model.
    Matrix4f model = Matrix4f::Identity(); //Matrix4f::Rotate(Matrix4f(1), Oc::Radians(90), { 0.5f, 1.0f, 0.0f });

    // We obtain uniforms from the register and indicate their respective values.
    registry.Get<Matrix4f>("proj").UpdateValue(proj);
    registry.Get<Matrix4f>("model").UpdateValue(model);
    registry.Get<Matrix4f>("view").UpdateValue(view);
}

void OnMoveCameraXY(const MouseMoveEvent& evt, Env& env)
{
    if (InputSystem::IsButtonDown(Input::Button::Middle))
    {
        auto& camera = env.MainCamera;
        Float dx = evt.PosRelX * env.CameraVelocity * camera.Radius;
        Float dy = evt.PosRelY * env.CameraVelocity * camera.Radius;
        camera = OrbitCamera::PanOrbitCamera(camera, dx, dy);
    }
}

void OnRotateCamera(const MouseMoveEvent& evt, Env& env)
{
    if (InputSystem::IsButtonDown(Input::Button::Left))
    {
        NP_DEBUG(Print, "PosRelX={} PosRelY={}", evt.PosRelX, evt.PosRelY);
        auto& camera = env.MainCamera;
        camera = OrbitCamera::RotateTheta(camera, evt.PosRelX * env.CameraVelocity);
        camera = OrbitCamera::RotatePhi(camera, -evt.PosRelY * env.CameraVelocity);
    }
}

void OnMoveCameraZOnScroll(const MouseWheelEvent& evt, Env& env)
{
    auto& camera = env.MainCamera;
    camera.Radius -= evt.Delta * env.CameraVelocity;
    if (camera.Radius < 3)
    {
        camera.Radius = 3;
    }
}

void Env::Init(Env& env)
{

    auto& window = env.MainWindow;
    auto& windowSignals = window.GetWindowSignals();

    windowSignals.OnMouseMove().Connect(
            [&](auto&, auto& evt)
            {
                OnMoveCameraXY(evt, env);
                OnRotateCamera(evt, env);
            });

    windowSignals.OnMouseWheel().Connect(
            [&](auto&, auto& evt)
            {
                OnMoveCameraZOnScroll(evt, env);
            });

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

}

void RenderCube(OpenGLVertexArray& vao, const OpenGLTexture2D& wall)
{
    // We bind the texture for the Cube.
    ActiveTexture(0);
    wall.Bind();

    // We draw the Cube.
    vao.Bind();
    glDrawArrays(GL_TRIANGLES, 0, 36);
}

void Env::Render(Env& env)
{
    Float width = env.MainWindow.GetWindowDefinition().Width;
    Float height = env.MainWindow.GetWindowDefinition().Height;

    glClearColor(0.2, 0.2, 0.4, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    UpdatePVM(*env.MainRenderer->Registry, env.MainCamera, env.MainWindow);
    RenderCube(*env.MainRenderer->VAO, env.MainRenderer->WallTexture);

    glViewport(0, 0, (Int) width, (Int) height);

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

Ptr<Renderer> Renderer::New()
{
    glEnable(GL_DEPTH_TEST);
    auto vao = MakeUnique<OpenGLVertexArray>();
    auto vbo = MakeUnique<OpenGLVertexBuffer>(Cube);

    LinkBuffer(*vbo, {
            { 0, 3, GL_FLOAT, sizeof(Vertex), nullptr },
            { 1, 2, GL_FLOAT, sizeof(Vertex), (VoidPtr)(3 * sizeof(Float)) },
    });

    OpenGLTexture2D wall = OpenGLTexture2D::LoadFromImage(
            ResourceManager::FromAssets("/Textures/Wall.jpg"),
            &DefaultParameterTexture);

    Path vertexFilepath = ResourceManager::FromAssets("/Shaders/MainVertex.glsl");
    Path fragmentFilepath = ResourceManager::FromAssets("/Shaders/MainFragment.glsl");
    auto program = MakeUnique<OpenGLShader>(
            ResourceManager::ReadStringContent(vertexFilepath),
            ResourceManager::ReadStringContent(fragmentFilepath));

    auto registry = MakeUnique<UniformRegistry>(*program);
    registry->Register("tex1", UInt32(wall))
        .Register("proj", Matrix4f(1))
        .Register("view", Matrix4f(1))
        .Register("model", Matrix4f(1));

    return MakeUnique<Renderer>
    (
        std::move(vao),
        std::move(vbo),
        wall,
        std::move(program),
        std::move(registry)
    );


}
