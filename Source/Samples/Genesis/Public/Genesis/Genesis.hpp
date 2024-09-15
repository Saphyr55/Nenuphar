#pragma once

#include "Genesis/RenderData.hpp"

#include "Nenuphar/ApplicationCore/Window.hpp"
#include "Nenuphar/Common/Type/Type.hpp"
#include "Nenuphar/Entity/Entity.hpp"
#include "Nenuphar/Entity/EntityRegistry.hpp"
#include "Nenuphar/Rendering/GraphicContext.hpp"

namespace Np = Nenuphar;

class GenesisApp
{
public:
    void OnInit();
    void OnTick();

public:
    GenesisApp();
    ~GenesisApp() = default;

private:
    Np::EntityRegistry Registry;
    Np::Entity ECamera;
    Np::Entity EFloor;
    Np::Entity EBarrel;
    Np::Entity ESponza;
    UniquePtr<Np::GraphicContext> MainGraphicContext;
    SharedRef<Np::Window> MainWindow;
    SharedRef<RenderData> MainRenderData;
};
