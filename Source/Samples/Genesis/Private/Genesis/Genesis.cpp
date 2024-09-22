#include "Genesis/Genesis.hpp"
#include "Genesis/Camera.hpp"
#include "Genesis/RenderData.hpp"
#include "Genesis/Transform.hpp"

#include "Nenuphar/ApplicationCore/Application.hpp"
#include "Nenuphar/ApplicationCore/WindowBase.hpp"
#include "Nenuphar/ApplicationCore/WindowSignals.hpp"
#include "Nenuphar/Asset/AssetRegistry.hpp"
#include "Nenuphar/Common/Type/Type.hpp"
#include "Nenuphar/Core/Debug.hpp"
#include "Nenuphar/Entity/EntityRegistry.hpp"
#include "Nenuphar/Graphics/Mesh.hpp"
#include "Nenuphar/Math/Camera.hpp"
#include "Nenuphar/Math/Matrix4.hpp"
#include "Nenuphar/Math/Vector3.hpp"
#include "Nenuphar/Model/Model.hpp"
#include "Nenuphar/Model/ModelAsset.hpp"
#include "Nenuphar/RenderLight/RenderTypes.hpp"
#include "Nenuphar/Rendering/CommandBuffer.hpp"
#include "Nenuphar/Rendering/CommandQueue.hpp"
#include "Nenuphar/Rendering/GraphicsContext.hpp"
#include "Nenuphar/Rendering/ImageAsset.hpp"
#include "Nenuphar/Rendering/RenderDevice.hpp"
#include "Nenuphar/Rendering/Shader.hpp"
#include "Nenuphar/Rendering/UniformRegistry.hpp"

#include <glad/glad.h>

namespace Np = Nenuphar;

static Vector3f GDefaultPosition(0.0f, 0.0f, 0.0f);

GenesisApp::GenesisApp()
{
}

Np::AppContext* GenesisApp::ProvideAppContext()
{
    return &Context;
}

Bool GenesisApp::OnInitialize()
{
    Np::AssetRegistry& assets = Np::AssetRegistry::Instance();
    assets.EmplaceLoader<Np::ImageAsset, Np::AssetOptions, Np::ImageAssetLoader>();
    assets.EmplaceLoader<Np::ModelAsset, Np::ModelAssetOptions, Np::ModelAssetLoader>();

    Np::WindowDefinition definition("Genesis Sample Application", 1080, 720);
    MainWindow = Np::WindowBase::Create(definition);
    Device = Np::RenderDevice::Create(Np::RenderAPI::OpenGL, MainWindow);
    MainRenderData = RenderData::Create(Device);

    // Camera entity.
    ECamera = Registry.Create();
    Registry.AddComponent<OrbitCamera>(ECamera, DefaultOrbitCameraFactory());
    Registry.AddComponent<Velocity>(ECamera, Velocity(0.005f));

    // Sponza entity.
    RenderableModel rSponzaModel;
    rSponzaModel.Model = std::move(MainRenderData.SponzaAsset->GetModel());
    RenderCommandSubmitModel(Device, rSponzaModel.Model);

    Transform sponzaTransform;
    sponzaTransform.Scale = Vector3f(0.1f);
    sponzaTransform.Translation = GDefaultPosition;

    ESponza = Registry.Create();
    Registry.AddComponent<Transform>(ESponza, sponzaTransform);
    Registry.AddComponent<RenderableModel>(ESponza, rSponzaModel);

    // Light source
    RenderableModel rLightModel;
    rLightModel.Model = CreateCubeModel();
    RenderCommandSubmitModel(Device, rLightModel.Model);

    Transform lightTransform;
    lightTransform.Scale = Vector3f(1.0f);
    lightTransform.Translation = Vector3f(0.0f, 355.0f, 0.0f);

    Np::Light light;
    light.Position = Vector3f(-1.0f, 1.0f, -1.0f);
    light.Ambient = Vector3f(0.2f, 0.2f, 0.2f);
    light.Diffuse = Vector3f(0.9f, 0.9f, 0.9f);
    light.Specular = Vector3f(0.0f, 0.0f, 0.0f);

    auto ELight = Registry.Create();
    Registry.AddComponent<Transform>(ELight, lightTransform);
    Registry.AddComponent<Np::Light>(ELight, light);
    Registry.AddComponent<RenderableModel>(ELight, rLightModel);

    auto& windowSignals = MainWindow->GetWindowSignals();

    auto& orbitCameraComponent = Registry.GetComponent<OrbitCamera>(ECamera);
    auto& cameraVelocity = Registry.GetComponent<Velocity>(ECamera);

    InitCamera(windowSignals, orbitCameraComponent, cameraVelocity);

    windowSignals.OnClose().Connect([&](auto&, auto&) {
        AppStopCurrent();
    });

    windowSignals.OnResize().ConnectHandler([&](const ResizeEvent& e) {
        OnTick(0.0);
    });

    MainWindow->Show();

    return true;
}

void GenesisApp::OnTick(Double deltaTime)
{
    Np::OrbitCamera& camera = Registry.GetComponent<OrbitCamera>(ECamera);

    Int width = MainWindow->GetWindowDefinition().Width;
    Int height = MainWindow->GetWindowDefinition().Height;

    Np::Viewport viewport;
    viewport.Width = width;
    viewport.Height = height;

    Vector4f backgroundColor(1.0f / 255, 10.0f / 255, 33.0f / 255, 255.0f / 255);

    SharedRef<Np::MainShaderProgram> shader = Device->GetMainShaderProgram();

    SharedRef<Np::CommandQueue> commandQueue = Device->CreateCommandQueue();
    SharedRef<Np::CommandBuffer> commandBuffer = Device->CreateCommandBuffer();

    commandBuffer->Clear();
    commandBuffer->ClearColor(backgroundColor);
    commandBuffer->SetViewport(viewport);
    commandBuffer->Record([&]() {
        Vector3f cameraPosition = camera.Position();

        // We obtain a projection matrix using the perspective matrix with a fov of 45
        // degrees, the window aspect, and 0.1 close up and 100 far away.
        Matrix4f projection = Matrix4f::Perspective(Np::Radians(45), width / (Float)height, 0.1f, 10000.0f);

        // We obtain the view in function of the camera.
        Matrix4f view = Matrix4f::LookAt(cameraPosition, camera.Target, camera.Up);

        shader->UpdateProjection(projection);
        shader->UpdateView(view);
        shader->GetRegistry()->Get<Vector3f>("UCameraPosition").UpdateValue(cameraPosition);
    });

    commandQueue->Submit(commandBuffer);

    MainRenderData.OnRenderData(commandQueue, Registry);

    commandQueue->Execute();

    Device->GetGraphicsContext()->SwapBuffers();
    MainWindow->PoolEvent();
}

void GenesisApp::OnClose()
{
}