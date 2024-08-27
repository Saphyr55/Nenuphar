#include "Genesis/Genesis.hpp"
#include "Genesis/Camera.hpp"
#include "Genesis/RenderData.hpp"
#include "Genesis/Transform.hpp"
#include "Nenuphar/ApplicationCore/WindowBase.hpp"
#include "Nenuphar/ApplicationCore/WindowDefinition.hpp"
#include "Nenuphar/Common/Type/Type.hpp"
#include "Nenuphar/Entity/EntityRegistry.hpp"
#include "Nenuphar/Math/Camera.hpp"
#include "Nenuphar/Math/Matrix4.hpp"
#include "Nenuphar/Math/Vector3.hpp"
#include "Nenuphar/Rendering/GraphicContext.hpp"
#include "Nenuphar/Rendering/RenderSystem.hpp"

#include <glad/glad.h>

namespace Np = Nenuphar;

GenesisApp::GenesisApp()
{
    Np::WindowDefinition definition("Genesis Sample Application", 1080, 720);
    MainWindow = Np::WindowBase::Create(definition);
    MainGraphicContext = Np::GraphicContext::Create(*MainWindow);
    MainRenderData = RenderData::Default();

    ECamera = Registry.Create();
    EFloor = Registry.Create();
    ECube = Registry.Create();

    OrbitCamera orbitCameraComponent(Radians(45.0f),
                                     Radians(45.0f), 3.0f,
                                     Vector3f(0.0, 0.0, 0.0),
                                     Vector3f(0.0f, 1.0f, 0.0f));

    Registry.AddComponent<OrbitCamera>(ECamera, orbitCameraComponent);
    Registry.AddComponent<Velocity>(ECamera, Velocity(0.005f));

    Transform eFloorTransform;
    eFloorTransform.Scale = Vector3f(1.0f);
    Registry.AddComponent<Transform>(EFloor, eFloorTransform);

    Transform eCubeTransform;
    eCubeTransform.Scale = Vector3f(1.0f);
    Registry.AddComponent<Transform>(ECube, eCubeTransform);
}


void GenesisApp::OnInit()
{
    auto& windowSignals = MainWindow->GetWindowSignals();

    auto& orbitCameraComponent = Registry.GetComponent<OrbitCamera>(ECamera);
    auto& cameraVelocity = Registry.GetComponent<Velocity>(ECamera);

    InitCamera(windowSignals, orbitCameraComponent, cameraVelocity);

    windowSignals.OnClose().Connect([&](auto&, auto&) {
        MainWindow->Destroy();
        Np::Engine::IsFinish = true;
    });

    windowSignals.OnResize().ConnectHandler([&](auto&) {
        OnRender();
    });

    MainWindow->Show();
}

void GenesisApp::OnUpdate()
{
    Np::OrbitCamera camera = Registry.GetComponent<OrbitCamera>(ECamera);

    Float width = MainWindow->GetWindowDefinition().Width;
    Float height = MainWindow->GetWindowDefinition().Height;

    // We obtain a projection matrix using the perspective matrix with a fov of 45 degrees,
    // the window aspect, and 0.1 close up and 100 far away.
    Matrix4f proj = Matrix4f::Perspective(Radians(45), (Float) width / height, 0.1f, 100.0f);

    // We obtain the view in function of the camera.
    Matrix4f view = Matrix4f::LookAt(camera.Position(), camera.Target, camera.Up);

    // We create the world model.
    // Matrix4f model = Matrix4f::Rotate(Matrix4f(1), Np::Radians(90), { 0.5f, 1.0f, 0.0f });
    Transform& transform = Registry.GetComponent<Transform>(EFloor);
    Matrix4f model = Transform::Tranformation(transform);

    // We obtain uniforms from the register and indicate their respective values.
    MainRenderData->Registry->Get<Matrix4f>("proj").UpdateValue(proj);
    MainRenderData->Registry->Get<Matrix4f>("model").UpdateValue(model);
    MainRenderData->Registry->Get<Matrix4f>("view").UpdateValue(view);
}

void GenesisApp::OnRender()
{
    Float width = MainWindow->GetWindowDefinition().Width;
    Float height = MainWindow->GetWindowDefinition().Height;

    Vector4f backgroundColor(0.58, 0.69, 0.8, 0.78);
    Np::RenderSystem::Instance().Clear(backgroundColor);

    OnRenderData(*MainRenderData);

    glViewport(0, 0, (Int) width, (Int) height);

    MainWindow->PoolEvent();
    MainGraphicContext->SwapBuffers();
}
