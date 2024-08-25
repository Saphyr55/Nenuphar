#include "Genesis/Genesis.hpp"
#include "Genesis/RenderData.hpp"
#include "Genesis/Transform.hpp"
#include "Nenuphar/ApplicationCore/WindowBase.hpp"
#include "Nenuphar/ApplicationCore/WindowDefinition.hpp"
#include "Nenuphar/Common/Instanciate.hpp"
#include "Nenuphar/Common/Type/Type.hpp"
#include "Nenuphar/Core/IO/Path.hpp"
#include "Nenuphar/Core/Resource/Resource.hpp"
#include "Nenuphar/Entity/Entity.hpp"
#include "Nenuphar/Entity/EntityRegistry.hpp"
#include "Nenuphar/InputSystem/InputSystem.hpp"
#include "Nenuphar/Math/Camera.hpp"
#include "Nenuphar/Math/Matrix4.hpp"
#include "Nenuphar/Math/Vector3.hpp"
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
    EFloor = m_registry.Create(); 

    OrbitCamera orbitCameraComponent(Radians(45.0f),
                                     Radians(45.0f), 3.0f,
                                     Vector3f(0.0, 0.0, 0.0),
                                     Vector3f(0.0f, 1.0f, 0.0f));

    m_registry.AddComponent<OrbitCamera>(MainCamera, orbitCameraComponent);

    Transform transform;
    transform.Scale = Vector3f(1.2f);
    m_registry.AddComponent<Transform>(EFloor, transform);
}

void OnUpdatePVM(Np::Entity& eFloor,
                 Np::EntityRegistry& entityRegistry,
                 Np::UniformRegistry& uniformRegistry,
                 const Np::OrbitCamera& camera,
                 const Np::Window& window)
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
    Transform& transform = entityRegistry.GetComponent<Transform>(eFloor);
    Matrix4f model = Transform::Tranformation(transform);

    // We obtain uniforms from the register and indicate their respective values.
    uniformRegistry.Get<Matrix4f>("proj").UpdateValue(proj);
    uniformRegistry.Get<Matrix4f>("model").UpdateValue(model);
    uniformRegistry.Get<Matrix4f>("view").UpdateValue(view);
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

void GenesisApp::OnInit()
{
    auto& windowSignals = MainWindow->GetWindowSignals();
    auto& orbitCameraComponent = m_registry.GetComponent<OrbitCamera>(MainCamera);

    windowSignals.OnKeyPressed().Connect([&](auto&, auto& evt) {
        ResetCameraTarget(evt, orbitCameraComponent);
    });

    windowSignals.OnMouseMove().Connect([&](auto&, auto& evt) {
        OnMoveCameraXY(evt, orbitCameraComponent);
        OnRotateCamera(evt, orbitCameraComponent);
    });

    windowSignals.OnMouseWheel().Connect([&](auto&, auto& evt) {
        OnMoveCameraZOnScroll(evt, orbitCameraComponent);
    });

    windowSignals.OnClose().Connect([&](auto&, auto&) {
        MainWindow->Destroy();
        Np::Engine::IsFinish = true;
    });

    windowSignals.OnResize().ConnectHandler([&](auto&) {
        OnRender();
    });

    MainWindow->Show();
}

void GenesisApp::OnRender()
{
    Float width = MainWindow->GetWindowDefinition().Width;
    Float height = MainWindow->GetWindowDefinition().Height;

    Np::RenderSystem::Instance().Clear(Vector4f(0.58, 0.69, 0.8, 0.78));
    auto& orbitCameraComponent = m_registry.GetComponent<OrbitCamera>(MainCamera);

    OnUpdatePVM(EFloor, m_registry, *MainRenderData->Registry, orbitCameraComponent, *MainWindow);
    OnRenderData(*MainRenderData);

    glViewport(0, 0, (Int) width, (Int) height);

    MainWindow->PoolEvent();
    MainGraphicContext->SwapBuffers();
}
