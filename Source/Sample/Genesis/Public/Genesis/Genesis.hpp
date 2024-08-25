#pragma once

#include "Genesis/RenderData.hpp"

#include "Nenuphar/ApplicationCore/Window.hpp"

#include "Nenuphar/Common/Type/Type.hpp"

#include "Nenuphar/InputSystem/Event.hpp"

#include "Nenuphar/Math/Camera.hpp"

#include "Nenuphar/Entity/Entity.hpp"
#include "Nenuphar/Entity/EntityRegistry.hpp"

#include "Nenuphar/Rendering/GraphicContext.hpp"
#include "Nenuphar/Rendering/Renderer.hpp"


namespace Np = Nenuphar;

class GenesisApp
{
public:
    void OnInit();
    void OnRender();

private:
    void ResetCameraTarget(const Np::KeyEvent& evt, Np::OrbitCamera& camera);
    void OnMoveCameraXY(const Np::MouseMoveEvent& evt, Np::OrbitCamera& camera);
    void OnRotateCamera(const Np::MouseMoveEvent& evt, Np::OrbitCamera& camera);
    void OnMoveCameraZOnScroll(const Np::MouseWheelEvent& evt, Np::OrbitCamera& camera);

public:
    GenesisApp();
    ~GenesisApp() = default;

private:
    Np::EntityRegistry m_registry;
    Np::Entity MainCamera;
    UniquePtr<Np::GraphicContext> MainGraphicContext;
    SharedRef<Np::Window> MainWindow;
    SharedRef<RenderData> MainRenderData;
    float CameraVelocity = 0.005f;
};
