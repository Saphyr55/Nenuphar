#include "Genesis/Genesis.hpp"
#include "Genesis/Camera.hpp"
#include "Genesis/GenesisApplicationMessageHandler.hpp"
#include "Genesis/RenderData.hpp"
#include "Genesis/Transform.hpp"


#include "Nenuphar/ApplicationCore/Application.hpp"
#include "Nenuphar/ApplicationCore/ApplicationMessageHandler.hpp"
#include "Nenuphar/ApplicationCore/PlatformApplication.hpp"
#include "Nenuphar/ApplicationCore/Window.hpp"
#include "Nenuphar/Asset/AssetRegistry.hpp"
#include "Nenuphar/Common/Instanciate.hpp"
#include "Nenuphar/Common/Type/Type.hpp"
#include "Nenuphar/Entity/Entity.hpp"
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

#include <glad/glad.h>

namespace Np = Nenuphar;

static Vector3f GDefaultPosition(0.0f, 0.0f, 0.0f);

GenesisApp::GenesisApp()
    : Cube(CreateCubeModel())
    , DeltaTime(0.0)
{
}

Np::AppContext* GenesisApp::ProvideAppContext()
{
    return &Context;
}

Bool GenesisApp::OnInitialize()
{
    EventHandler = MakeSharedRef<WindowEventHandler>();

    Np::SharedRef<Np::ApplicationMessageHandler> messageHandler = 
        MakeSharedRef<GenesisApplicationMessageHandler>(EventHandler);

    Np::PlatformAppGet()->SetApplicationMessageHandler(messageHandler);

    Np::AssetRegistry& assets = Np::AssetRegistry::Instance();
    assets.EmplaceLoader<Np::ImageAsset, Np::AssetOptions, Np::ImageAssetLoader>();
    assets.EmplaceLoader<Np::ModelAsset, Np::ModelAssetOptions, Np::ModelAssetLoader>();

    Np::WindowDefinition definition("Genesis Sample Application", 1080, 720);

    MainWindow = Np::PlatformAppGet()->MakeWindow(definition);
    Device = Np::RenderDevice::Create(Np::RenderAPI::OpenGL, MainWindow);
    MainRenderData = RenderData::Create(Device);

    EventHandler->SetWindow(MainWindow);

    EventHandler->OnClose().ConnectHandler([&](auto) {
        MainWindow->Destroy();
        Np::AppStopCurrent();
    });

    EventHandler->OnResize().ConnectHandler([&](auto& event) {
        OnTick(GetDeltaTime());
    });

    // Camera entity.
    ECamera = Registry.Create();
    Registry.AddComponent<OrbitCamera>(ECamera, DefaultOrbitCameraFactory());
    Registry.AddComponent<Velocity>(ECamera, Velocity(0.005f));

    // Sponza entity.
    RenderableModel rSponzaModel;
    rSponzaModel.Model = &MainRenderData.SponzaAsset->GetModel();
    RenderCommandSubmitModel(Device, *rSponzaModel.Model);

    Transform sponzaTransform;
    sponzaTransform.Scale = Vector3f(0.1f);
    sponzaTransform.Translation = GDefaultPosition;

    ESponza = Registry.Create();
    Registry.AddComponent<Transform>(ESponza, sponzaTransform);
    Registry.AddComponent<RenderableModel>(ESponza, rSponzaModel);

    // Light source
    RenderableModel rLightModel;
    rLightModel.Model = &Cube;
    RenderCommandSubmitModel(Device, *rLightModel.Model);

    Transform lightTransform;
    lightTransform.Scale = Vector3f(1.0f);
    lightTransform.Translation = Vector3f(0.0f, 355.0f, 0.0f);

    Np::Light light;
    light.Position = Vector3f(-1.0f, 1.0f, -1.0f);
    light.Ambient = Vector3f(0.2f, 0.2f, 0.2f);
    light.Diffuse = Vector3f(0.9f, 0.9f, 0.9f);
    light.Specular = Vector3f(0.0f, 0.0f, 0.0f);

    Np::Entity ELight = Registry.Create();
    Registry.AddComponent<Transform>(ELight, lightTransform);
    Registry.AddComponent<Np::Light>(ELight, light);
    Registry.AddComponent<RenderableModel>(ELight, rLightModel);

    auto& orbitCameraComponent = Registry.GetComponent<OrbitCamera>(ECamera);
    auto& cameraVelocity = Registry.GetComponent<Velocity>(ECamera);

    InitCamera(EventHandler, orbitCameraComponent, cameraVelocity);
    CommandQueue = Device->CreateCommandQueue();

    MainWindow->Show();

    return true;
}

void GenesisApp::OnTick(Double deltaTime)
{
    DeltaTime = deltaTime;
    
    Np::OrbitCamera& camera = Registry.GetComponent<OrbitCamera>(ECamera);

    Int width = MainWindow->GetWindowDefinition().Width;
    Int height = MainWindow->GetWindowDefinition().Height;

    Vector3f cameraPosition = camera.Position();

    // We obtain a projection matrix using the perspective matrix with a fov of 45
    // degrees, the window aspect, and 0.1 close up and 100 far away.
    Matrix4f projection = Matrix4f::Perspective(Np::Radians(45), width / (Float)height, 0.1f, 10000.0f);

    // We obtain the view in function of the camera.
    Matrix4f view = Matrix4f::LookAt(cameraPosition, camera.Target, camera.Up);

    Np::Viewport viewport;
    viewport.Width = width;
    viewport.Height = height;
    viewport.X = 0;
    viewport.Y = 0;

    Vector4f backgroundColor(1 / 255.0f, 10 / 255.0f, 33 / 255.0f, 255 / 255.0f);

    SharedRef<Np::MainShaderProgram> shader = Device->GetMainShaderProgram();

    SharedRef<Np::CommandBuffer> commandBuffer = Device->CreateCommandBuffer();

    commandBuffer->Clear();
    commandBuffer->ClearColor(backgroundColor);
    commandBuffer->SetViewport(viewport);

    commandBuffer->Record([&] {
        shader->UpdateProjection(projection);
        shader->UpdateView(view);
        shader->GetRegistry()->Get<Vector3f>("UCameraPosition").UpdateValue(cameraPosition);
    });

    MainRenderData.OnRenderData(commandBuffer, Registry);

    CommandQueue->Submit(commandBuffer);
    CommandQueue->Execute();

    Device->GetGraphicsContext()->SwapBuffers();
}

void GenesisApp::OnClose()
{
    for (auto& [e, transform, rModel]: Registry.View<Transform, RenderableModel>())
    {
        rModel.Model->Destroy();
    }

    for (auto& [e, light, transform, rModel]: Registry.View<Np::Light, Transform, RenderableModel>())
    {
        rModel.Model->Destroy();
    }
}

double GenesisApp::GetDeltaTime()
{
    return DeltaTime;
}