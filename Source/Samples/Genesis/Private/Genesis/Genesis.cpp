#include "Genesis/Genesis.hpp"
#include "Genesis/Camera.hpp"
#include "Genesis/RenderData.hpp"
#include "Genesis/Transform.hpp"

#include "Nenuphar/ApplicationCore/WindowBase.hpp"
#include "Nenuphar/ApplicationCore/WindowSignals.hpp"
#include "Nenuphar/Common/Type/Type.hpp"
#include "Nenuphar/Entity/EntityRegistry.hpp"
#include "Nenuphar/Math/Camera.hpp"
#include "Nenuphar/Math/Matrix4.hpp"
#include "Nenuphar/Math/Vector3.hpp"
#include "Nenuphar/Model/Model.hpp"
#include "Nenuphar/RenderLight/RenderTypes.hpp"
#include "Nenuphar/Rendering/GraphicContext.hpp"
#include "Nenuphar/Rendering/RenderService.hpp"
#include "Nenuphar/Rendering/Material.hpp"

#include <glad/glad.h>

namespace Np = Nenuphar;

GenesisApp::GenesisApp()
{
    Vector3f normalPosition(0.0f, 0.0f, 0.0f);
    Np::WindowDefinition definition("Genesis Sample Application", 1080, 720);
    MainWindow = Np::WindowBase::Create(definition);
    MainGraphicContext = Np::GraphicContext::Create(*MainWindow);
    auto [data, rModels] = RenderData::Default();
    MainRenderData = data;

    // Camera entity.
    ECamera = Registry.Create();
    Registry.AddComponent<OrbitCamera>(ECamera, DefaultOrbitCameraFactory());
    Registry.AddComponent<Velocity>(ECamera, Velocity(0.005f));

/*
    // Floor entity.
    Colorable rFloorColorable;
    Vector4f floorColor(GDefaultColor);
    floorColor.w = floorColor.w / 2;
    rFloorColorable.Color = floorColor;

    RenderableModel rFloorModel;
    rFloorModel.Model = rModels.FloorModelId;

    Transform floorTransform;
    floorTransform.Scale = Vector3f(1000.0f);
    floorTransform.Translation = Vector3f(0.0f, 0.0f, 0.0f);;

    EFloor = Registry.Create();
    Registry.AddComponent<Transform>(EFloor, floorTransform);
    Registry.AddComponent<RenderableModel>(EFloor, rFloorModel);
    Registry.AddComponent<Colorable>(EFloor, rFloorColorable);

    // Barrel entity.
    RenderableModel rBarrelModel;
    rBarrelModel.Model = rModels.BarrelModelId;

    Transform barrelTransform;
    barrelTransform.Scale = Vector3f(3.0f);
    barrelTransform.Translation = normalPosition;

    EBarrel = Registry.Create();
    Registry.AddComponent<Transform>(EBarrel, barrelTransform);
    Registry.AddComponent<RenderableModel>(EBarrel, rBarrelModel);
*/
    
    // Sponza entity.
    RenderableModel rSponzaModel;
    rSponzaModel.Model = rModels.SponzaModelId;

    Transform sponzaTransform;
    sponzaTransform.Scale = Vector3f(0.1f);
    sponzaTransform.Translation = normalPosition;

    ESponza = Registry.Create();
    Registry.AddComponent<Transform>(ESponza, sponzaTransform);
    Registry.AddComponent<RenderableModel>(ESponza, rSponzaModel);

    Model cubeModel = CubeModelFactory();
    ModelId cubeModelId = data->Renderer->PersistModel(cubeModel);

    // Light source
    RenderableModel rLightModel;
    rLightModel.Model = cubeModelId;

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

    windowSignals.OnResize().ConnectHandler([&](const ResizeEvent& e) {
        OnTick();
    });

    MainWindow->Show();
}

void GenesisApp::OnTick()
{
    Np::OrbitCamera& camera = Registry.GetComponent<OrbitCamera>(ECamera);
    Vector3f cameraPosition = camera.Position();

    Float width = MainWindow->GetWindowDefinition().Width;
    Float height = MainWindow->GetWindowDefinition().Height;

    // We obtain a projection matrix using the perspective matrix with a fov of 45
    // degrees, the window aspect, and 0.1 close up and 100 far away.
    Matrix4f proj = Matrix4f::Perspective(Np::Radians(45), width / height, 0.1f, 10000.0f);

    // We obtain the view in function of the camera.
    Matrix4f view = Matrix4f::LookAt(cameraPosition, camera.Target, camera.Up);

    MainRenderData->MaterialRegistry.Get<Matrix4f>("proj").UpdateValue(proj);
    MainRenderData->MaterialRegistry.Get<Matrix4f>("view").UpdateValue(view);
    MainRenderData->MaterialRegistry.Get<Vector3f>("UCameraPosition").UpdateValue(cameraPosition);

    Vector4f backgroundColor(1.0f / 255, 10.0f / 255, 33.0f / 255, 255.0f / 255);
    Np::RenderService::Instance()->Clear(backgroundColor);

    OnRenderData(*MainRenderData, Registry);

    glViewport(0, 0, (Int) width, (Int) height);

    MainWindow->PoolEvent();
    MainGraphicContext->SwapBuffers();
}
