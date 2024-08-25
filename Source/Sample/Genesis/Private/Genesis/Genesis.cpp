#include "Genesis/Genesis.hpp"
#include "Nenuphar/ApplicationCore/WindowBase.hpp"
#include "Nenuphar/ApplicationCore/WindowDefinition.hpp"
#include "Nenuphar/Common/Instanciate.hpp"
#include "Nenuphar/Common/Type/Type.hpp"
#include "Nenuphar/Core/IO/Path.hpp"
#include "Nenuphar/Core/Resource/Resource.hpp"
#include "Nenuphar/InputSystem/InputSystem.hpp"
#include "Nenuphar/Math/Camera.hpp"
#include "Nenuphar/Model/TOL/TOLMeshLoader.hpp"
#include "Nenuphar/Rendering/GraphicContext.hpp"
#include "Nenuphar/Rendering/OpenGL/OpenGLBuffer.hpp"
#include "Nenuphar/Rendering/OpenGL/OpenGLTexture.hpp"
#include "Nenuphar/Rendering/OpenGL/OpenGLRenderer.hpp"
#include "Nenuphar/Rendering/RenderSystem.hpp"
#include "Nenuphar/Rendering/Texture.hpp"
#include "Nenuphar/Rendering/Vertex.hpp"
#include "Nenuphar/Model/TOL/TOLMeshLoader.hpp"

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
    {
        Np::WindowDefinition definition("Genesis Sample Application", 1080, 720);
        MainWindow = Np::WindowBase::Create(definition);
        MainGraphicContext = Np::GraphicContext::Create(*MainWindow);
        MainRenderData = RenderData::Default();

        MainCamera = m_registry.Create();
        Renderer = MakeUnique<Np::OpenGLRenderer>();

        OrbitCamera orbitCameraComponent(Radians(45.0f),
                                         Radians(45.0f), 3.0f,
                                         Vector3f(0.0, 0.0, 0.0),
                                         Vector3f(0.0f, 1.0f, 0.0f));

        m_registry.AddComponent<OrbitCamera>(MainCamera, orbitCameraComponent);
    }

    void UpdatePVM(Np::UniformRegistry& registry, const Np::OrbitCamera& camera, const Np::Window& window)
    {
        Float width = window.GetWindowDefinition().Width;
        Float height = window.GetWindowDefinition().Height;

        // We obtain a projection matrix using the perspective matrix with a fov of 45 degrees,
        // the window aspect, and 0.1 close up and 100 far away.
        Matrix4f proj = Matrix4f::Perspective(Radians(45), (Float) width / height, 0.1f, 100.0f);

        // We obtain the view in function of the camera.
        Matrix4f view = Matrix4f::LookAt(camera.Position(), camera.Target, camera.Up);

        // We create the world model.
        // Matrix4f model = Matrix4f::Rotate(Matrix4f(1), Np::Radians(90), { 0.5f, 1.0f, 0.0f });
        Matrix4f model = Matrix4f::Identity();
        
        // We obtain uniforms from the register and indicate their respective values.
        registry.Get<Matrix4f>("proj").UpdateValue(proj);
        registry.Get<Matrix4f>("model").UpdateValue(model);
        registry.Get<Matrix4f>("view").UpdateValue(view);
    }

    void GenesisApp::ResetCameraTarget(const Np::KeyEvent& evt, Np::OrbitCamera& camera)
    {
        if (evt.Key == Input::Key::R)
        {
            camera.Target = DefaultCamera.Target;
        }
    }

    void GenesisApp::OnMoveCameraXY(const Np::MouseMoveEvent& evt, Np::OrbitCamera& camera)
    {
        if (Np::InputSystem::IsButtonDown(Input::Button::Middle))
        {
            Float dx = -evt.PosRelX * (CameraVelocity * 0.1f) * camera.Radius;
            Float dy = -evt.PosRelY * (CameraVelocity * 0.1f) * camera.Radius;
            camera = OrbitCamera::PanOrbitCamera(camera, dx, dy);
        }
    }

    void GenesisApp::OnRotateCamera(const Np::MouseMoveEvent& evt, Np::OrbitCamera& camera)
    {
        if (Np::InputSystem::IsButtonDown(Input::Button::Left))
        {
            camera = OrbitCamera::RotateTheta(camera, evt.PosRelX * CameraVelocity);
            camera = OrbitCamera::RotatePhi(camera, -evt.PosRelY * CameraVelocity);
        }
    }

    void GenesisApp::OnMoveCameraZOnScroll(const Np::MouseWheelEvent& evt, Np::OrbitCamera& camera)
    {
        camera.Radius -= evt.Delta * CameraVelocity;
        if (camera.Radius < 3)
        {
            camera.Radius = 3;
        }
    }

    void GenesisApp::Init()
    {
        auto& windowSignals = MainWindow->GetWindowSignals();
        auto& orbitCameraComponent = m_registry.GetComponent<OrbitCamera>(MainCamera);

        windowSignals.OnKeyPressed().Connect([&](auto&, auto& evt)
        {
            ResetCameraTarget(evt, orbitCameraComponent);
        });

        windowSignals.OnMouseMove().Connect([&](auto&, auto& evt)
        {
            OnMoveCameraXY(evt, orbitCameraComponent);
            OnRotateCamera(evt, orbitCameraComponent);
        });

        windowSignals.OnMouseWheel().Connect([&](auto&, auto& evt)
        {
            OnMoveCameraZOnScroll(evt, orbitCameraComponent);
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

    void RenderCube(Np::OpenGLVertexArray& vao, const Np::OpenGLTexture2D& wall)
    {
        // We bind the texture for the Cube.
        Np::ActiveTexture(0);
        wall.Bind();

        // We draw the Cube.
        vao.Bind();
        glDrawArrays(GL_TRIANGLES, 0, 36);
    }

    void GenesisApp::Render()
    {
        Float width = MainWindow->GetWindowDefinition().Width;
        Float height = MainWindow->GetWindowDefinition().Height;

        Np::RenderSystem::Instance().Clear(Vector4f(0.58, 0.69, 0.8, 0.78));
        auto& orbitCameraComponent = m_registry.GetComponent<OrbitCamera>(MainCamera);

        UpdatePVM(*MainRenderData->Registry, orbitCameraComponent, *MainWindow);
        RenderCube(*MainRenderData->VAO, MainRenderData->WallTexture);

        glViewport(0, 0, (Int) width, (Int) height);

        MainWindow->PoolEvent();
        MainGraphicContext->SwapBuffers();
    }

    SharedRef<RenderData> RenderData::Default()
    {
        Np::RenderSystem::Instance().Enable();

        auto cubePathObj = Np::FromAssets("/Models/Cube.obj");
        auto pathWall = Np::FromAssets("/Textures/Wall.jpg");
        auto wall = Np::OpenGLTexture2D::LoadFromImage(pathWall, &DefaultParameterTexture);

        auto vao = MakeUnique<Np::OpenGLVertexArray>();
        auto vbo = MakeUnique<Np::OpenGLArrayBuffer<VertexMinimalInfo>>(CubeVertices);
        
        TOLModelLoader modelLoader;
        auto res = modelLoader.Load(cubePathObj);
        if (!res.HasValue())
        {
            return nullptr;
        }

        auto model = res.Value();
        
        LinkBuffer(*vbo, LayoutVertex);

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
        registry->Register("tex1", Texture(wall))
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
