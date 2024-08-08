#include "Genesis/Genesis.hpp"
#include "Nenuphar/ApplicationCore/WindowBase.hpp"
#include "Nenuphar/ApplicationCore/WindowDefinition.hpp"
#include "Nenuphar/ApplicationCore/WindowInterface.hpp"
#include "Nenuphar/Common/Instanciate.hpp"
#include "Nenuphar/Common/Type/Type.hpp"
#include "Nenuphar/InputSystem/InputSystem.hpp"
#include "Nenuphar/Rendering/GraphicContext.hpp"
#include "Nenuphar/Rendering/OpenGL/OpenGLBuffer.hpp"
#include "Nenuphar/Rendering/OpenGL/OpenGLTexture.hpp"
#include "Nenuphar/Rendering/RenderSystem.hpp"

#include <glad/glad.h>

namespace Np = Nenuphar;

namespace gn
{


    static OrbitCamera DefaultCamera((float) Radians(45.0f),
                                     (float) Radians(45.0f),
                                     3.0f,
                                     Vector3f(0.0, 0.0, 0.0),
                                     Vector3f(0.0f, 1.0f, 0.0f));

    GenesisApp::GenesisApp()
        : MainCamera((Float) Radians(45.0f),
                     (Float) Radians(45.0f),
                     3.0f,
                     Vector3f(0.0, 0.0, 0.0),
                     Vector3f(0.0f, 1.0f, 0.0f))
    {
        Np::WindowDefinition definition("Genesis Sample Application", 1080, 720);
        MainWindow = Np::WindowBase::Create(definition);
        MainGraphicContext = Np::GraphicContext::Create(*MainWindow);
        MainRenderData = RenderData::Default();
    }

    void UpdatePVM(Np::UniformRegistry& registry, const Np::OrbitCamera& camera, const Np::WindowInterface& window)
    {

        Float width = window.GetWindowDefinition().Width;
        Float height = window.GetWindowDefinition().Height;

        // We obtain a projection matrix using the perspective matrix with a fov of 45 degrees,
        // the window aspect, and 0.1 close up and 100 far away.
        Matrix4f proj = Matrix4f::Perspective(Radians(45), (Float) width / height, 0.1f, 100.0f);

        // We obtain the view in function of the camera.
        Matrix4f view = Matrix4f::LookAt(camera.Position(), camera.Target, camera.Up);

        // We create the world model.
        Matrix4f model = Matrix4f::Identity();//Matrix4f::Rotate(Matrix4f(1), Oc::Radians(90), { 0.5f, 1.0f, 0.0f });

        // We obtain uniforms from the register and indicate their respective values.
        registry.Get<Matrix4f>("proj").UpdateValue(proj);
        registry.Get<Matrix4f>("model").UpdateValue(model);
        registry.Get<Matrix4f>("view").UpdateValue(view);
    }

    void GenesisApp::ResetCameraTarget(const Np::KeyEvent& evt)
    {
        if (evt.Key == Input::Key::R)
        {
            MainCamera.Target = DefaultCamera.Target;
        }
    }

    void GenesisApp::OnMoveCameraXY(const Np::MouseMoveEvent& evt)
    {
        if (Np::InputSystem::IsButtonDown(Input::Button::Middle))
        {
            auto& camera = MainCamera;
            Float dx = -evt.PosRelX * (CameraVelocity * 0.1f) * camera.Radius;
            Float dy = -evt.PosRelY * (CameraVelocity * 0.1f) * camera.Radius;
            camera = OrbitCamera::PanOrbitCamera(camera, dx, dy);
        }
    }

    void GenesisApp::OnRotateCamera(const Np::MouseMoveEvent& evt)
    {
        if (Np::InputSystem::IsButtonDown(Input::Button::Left))
        {
            MainCamera = OrbitCamera::RotateTheta(MainCamera, evt.PosRelX * CameraVelocity);
            MainCamera = OrbitCamera::RotatePhi(MainCamera, -evt.PosRelY * CameraVelocity);
        }
    }

    void GenesisApp::OnMoveCameraZOnScroll(const Np::MouseWheelEvent& evt)
    {
        MainCamera.Radius -= evt.Delta * CameraVelocity;
        if (MainCamera.Radius < 3)
        {
            MainCamera.Radius = 3;
        }
    }

    void GenesisApp::Init()
    {
        auto& windowSignals = MainWindow->GetWindowSignals();

        windowSignals.OnKeyPressed().Connect([&](auto&, auto& evt)
        {
            ResetCameraTarget(evt);
        });

        windowSignals.OnMouseMove().Connect([&](auto&, auto& evt)
        {
            OnMoveCameraXY(evt);
            OnRotateCamera(evt);
        });

        windowSignals.OnMouseWheel().Connect([&](auto&, auto& evt)
        {
            OnMoveCameraZOnScroll(evt);
        });

        windowSignals.OnClose().Connect([&](auto&, auto&)
        {
            MainWindow->Destroy();
            Np::Engine::IsFinish = true;
        });

        windowSignals.OnResize().ConnectHandler([&](auto&)
        {
            Render();
        });

        MainWindow->Show();
    }

    void RenderCube(Np::OpenGLVertexArray& vao, const Np::TextureID& wall)
    {
        // We bind the texture for the Cube.
        Np::ActiveTexture(wall);

        // We draw the Cube.
        vao.Bind();
        glDrawArrays(GL_TRIANGLES, 0, 36);
    }

    void GenesisApp::Render()
    {
        Float width = MainWindow->GetWindowDefinition().Width;
        Float height = MainWindow->GetWindowDefinition().Height;

        Np::RenderSystem::Instance().Clear(Vector4f(0.2, 0.2, 0.4, 1));

        UpdatePVM(*MainRenderData->Registry, MainCamera, *MainWindow);
        RenderCube(*MainRenderData->VAO, MainRenderData->WallTexture);

        glViewport(0, 0, (Int) width, (Int) height);

        MainWindow->PoolEvent();
        MainGraphicContext->SwapBuffers();
    }

    SharedRef<RenderData> RenderData::Default()
    {
        Np::RenderSystem::Instance().Enable();

        auto wall = Np::RenderSystem::Instance()
                            .MakeTexture2D(Np::ResourceManager::FromAssets("/Textures/Wall.jpg"));

        auto vao = MakeUnique<Np::OpenGLVertexArray>();
        auto vbo = MakeUnique<Np::OpenGLVertexBuffer>(CubeVertices);

        LinkBuffer(*vbo, LayoutVertex);

        Path vertexFilepath = Np::ResourceManager::FromAssets("/Shaders/MainVertex.glsl");
        Path fragmentFilepath = Np::ResourceManager::FromAssets("/Shaders/MainFragment.glsl");

        auto program = MakeUnique<Np::OpenGLShader>(
                Np::ResourceManager::ReadStringContent(vertexFilepath),
                Np::ResourceManager::ReadStringContent(fragmentFilepath));

        auto registry = MakeUnique<Np::UniformRegistry>(*program);
        registry->Register("tex1", wall)
                .Register("proj", Matrix4f(1))
                .Register("view", Matrix4f(1))
                .Register("model", Matrix4f(1));

        return MakeSharedRef<RenderData>(
            std::move(vao),
            std::move(vbo),
            wall,
            std::move(program),
            std::move(registry)
        );
    }
    
}
