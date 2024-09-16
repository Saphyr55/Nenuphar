#pragma once

#include "Genesis/RenderData.hpp"

#include "Nenuphar/ApplicationCore/Application.hpp"
#include "Nenuphar/ApplicationCore/Window.hpp"
#include "Nenuphar/Common/Type/Type.hpp"
#include "Nenuphar/Entity/Entity.hpp"
#include "Nenuphar/Entity/EntityRegistry.hpp"
#include "Nenuphar/Rendering/GraphicContext.hpp"

namespace Np = Nenuphar;


class GenesisApp : public Np::AppDelegate
{
public:
    virtual Np::AppContext* ProvideAppContext() override;

    virtual void OnInitialize() override;

    virtual void OnTick(Double deltaTime) override;

    virtual void OnClose() override;

public:
    GenesisApp();
    ~GenesisApp() = default;

private:
    Np::AppContext Context;
    Np::EntityRegistry Registry;
    Np::Entity ECamera;
    Np::Entity EFloor;
    Np::Entity EBarrel;
    Np::Entity ESponza;
    UniquePtr<Np::GraphicContext> MainGraphicContext;
    SharedRef<Np::Window> MainWindow;
    SharedRef<RenderData> MainRenderData;
};
