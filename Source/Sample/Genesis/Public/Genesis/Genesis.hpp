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
    void OnUpdate();

public:
    GenesisApp();
    ~GenesisApp() = default;

private:
    Np::EntityRegistry Registry;
    Np::Entity ECamera;
    Np::Entity EFloor;
    Np::Entity ECube;
    Np::Entity EBunny;
    Np::Entity EBarrel; 
    UniquePtr<Np::GraphicContext> MainGraphicContext;
    SharedRef<Np::Window> MainWindow;
    SharedRef<RenderData> MainRenderData;
};
