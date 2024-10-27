#include "StanfordBunny/StanfordBunnyApp.hpp"
#include "Nenuphar/Core/Debug.hpp"
#include "StanfordBunny/Camera.hpp"
#include "StanfordBunny/SBApplicationMessageHandler.hpp"
#include "StanfordBunny/RenderData.hpp"
#include "StanfordBunny/Transform.hpp"


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

#include <array>
#include <glad/glad.h>

namespace Np = Nenuphar;

static Vector3f GDefaultPosition(0.0f, 5.0f, 0.0f);

StanfordBunnyApp::StanfordBunnyApp()
    : Cube(CreateCubeModel())
    , DeltaTime(0.0)
{
}

Np::AppContext* StanfordBunnyApp::ProvideAppContext()
{
    return &Context;
}

Bool StanfordBunnyApp::OnInitialize()
{
    EventHandler = MakeSharedRef<WindowEventHandler>();

    Np::SharedRef<Np::ApplicationMessageHandler> messageHandler =
            MakeSharedRef<SBApplicationMessageHandler>(EventHandler);

    Np::PlatformAppGet()->SetApplicationMessageHandler(messageHandler);

    Np::AssetRegistry& assets = Np::AssetRegistry::Instance();
    assets.EmplaceLoader<Np::ImageAsset, Np::AssetOptions, Np::ImageAssetLoader>();
    assets.EmplaceLoader<Np::ModelAsset, Np::ModelAssetOptions, Np::ModelAssetLoader>();

    Np::WindowDefinition definition("Stanford Bunny", 1080, 720);

    MainWindow = Np::PlatformAppGet()->MakeWindow(definition);
    Device = Np::RenderDevice::Create(Np::RenderAPI::OpenGL, MainWindow);
    MainRenderData = RenderData::Create(Device);
    
    EventHandler->SetWindow(MainWindow);

    EventHandler->OnClose().ConnectHandler([&](auto) {
        MainWindow->Destroy();
        Np::AppStopCurrent();
    });

    EventHandler->OnResize().ConnectHandler([&](auto& event) {
        if (Np::AppGetCurrent()->IsRunning())
        {
            OnTick(GetDeltaTime());
        }
    });

    // Camera entity.
    ECamera = Registry.Create();
    Registry.AddComponent<OrbitCamera>(ECamera, DefaultOrbitCameraFactory());
    Registry.AddComponent<Velocity>(ECamera, Velocity(0.005f));

    // Bunny entity.
    RenderableModel rBunnyModel;
    rBunnyModel.Model = &MainRenderData.BunnyAsset->GetModel();
    RenderCommandSubmitModel(Device, *rBunnyModel.Model);

    Transform bunnyTransform;
    bunnyTransform.Scale = Vector3f(2.0f);
    bunnyTransform.Translation = GDefaultPosition;

    EBunny = Registry.Create();
    Registry.AddComponent<Transform>(EBunny, bunnyTransform);
    Registry.AddComponent<RenderableModel>(EBunny, rBunnyModel);

    Np::Light light;
    light.Position = Vector3f(0.0f, 10.0f, 0.0f);
    light.Ambient = Vector3f(0.2f, 0.2f, 0.2f);
    light.Diffuse = Vector3f(0.9f, 0.9f, 0.9f);
    light.Specular = Vector3f(1.0f);

    Np::Entity ELight = Registry.Create();
    Registry.AddComponent<Np::Light>(ELight, light);

    auto& orbitCameraComponent = Registry.GetComponent<OrbitCamera>(ECamera);
    auto& cameraVelocity = Registry.GetComponent<Velocity>(ECamera);

    InitCamera(EventHandler, orbitCameraComponent, cameraVelocity);

    CommandQueue = Device->CreateCommandQueue();

    MainWindow->Show();
        
    ImageAssetOptions skyboxLoadOptions;
    skyboxLoadOptions.Flip = false;
    
    Skybox = Device->CreateSkybox({
        assets.Load<ImageAsset>("/skybox/skybox/right.jpg", skyboxLoadOptions),
        assets.Load<ImageAsset>("/skybox/skybox/left.jpg", skyboxLoadOptions),
        assets.Load<ImageAsset>("/skybox/skybox/top.jpg", skyboxLoadOptions),
        assets.Load<ImageAsset>("/skybox/skybox/bottom.jpg", skyboxLoadOptions),
        assets.Load<ImageAsset>("/skybox/skybox/front.jpg", skyboxLoadOptions),
        assets.Load<ImageAsset>("/skybox/skybox/back.jpg", skyboxLoadOptions)
    });
    NCHECK(Skybox)
    

    return true;
}

void StanfordBunnyApp::OnTick(Double deltaTime)
{
    DeltaTime = deltaTime;

    Np::OrbitCamera& camera = Registry.GetComponent<OrbitCamera>(ECamera);

    Int width = MainWindow->GetWindowDefinition().Width;
    Int height = MainWindow->GetWindowDefinition().Height;
    Float aspect = width / (Float) height;

    // We obtain a projection matrix using the perspective matrix with a fov of 45
    // degrees, the window aspect, and 0.1 close up and 100 far away.
    Matrix4f projection = Matrix4f::Perspective(Np::Radians(45), aspect, 0.1f, 10000.0f);

    // We obtain the view in function of the camera.
    Matrix4f view = Matrix4f::LookAt(camera.Position(), camera.Target, camera.Up);

    Np::Viewport viewport;
    viewport.Width = width;
    viewport.Height = height;
    viewport.X = 0;
    viewport.Y = 0;
    
    Vector4f backgroundColor(240 / 255.0f, 240 / 255.0f, 240 / 255.0f, 240 / 255.0f);
    
    SharedRef<Np::MaterialShaderProgram> shader = Device->GetMaterialShaderProgram();
    SharedRef<Np::SkyboxShaderProgram> skyboxShader = Device->GetSkyboxShaderProgram();

    SharedRef<Np::CommandBuffer> commandBuffer = Device->CreateCommandBuffer();
    
    commandBuffer->Clear();
    commandBuffer->ClearColor(backgroundColor);
    commandBuffer->SetViewport(viewport);
    
    RenderCommand updateProjectionView = Device->CreateProjectionViewCommand(projection, view);
    commandBuffer->Record(updateProjectionView);
    
    commandBuffer->Record([&] {
        shader->GetRegistry()->Get<Vector3f>("UCameraPosition").UpdateValue(camera.Position());
    });

    MainRenderData.OnRenderData(commandBuffer, Registry);
    
    commandBuffer->RenderSkybox(skyboxShader, Skybox, projection, view);

    CommandQueue->Submit(commandBuffer);
    CommandQueue->Execute();

    Device->GetGraphicsContext()->SwapBuffers();
}

void StanfordBunnyApp::OnClose()
{
    for (auto& [e, transform, rModel]: Registry.View<Transform, RenderableModel>())
    {
        rModel.Model->Destroy();
    }

    for (auto& [e, light, transform, rModel]: Registry.View<Np::Light, Transform, RenderableModel>())
    {
        rModel.Model->Destroy();
    }

    Skybox->Destroy();
}

double StanfordBunnyApp::GetDeltaTime()
{
    return DeltaTime;
}