#pragma once

#include "Genesis/RenderData.hpp"

#include "Nenuphar/ApplicationCore/Application.hpp"
#include "Nenuphar/ApplicationCore/Window.hpp"
#include "Nenuphar/Common/Type/Type.hpp"
#include "Nenuphar/Entity/Entity.hpp"
#include "Nenuphar/Entity/EntityRegistry.hpp"
#include "Nenuphar/Model/Model.hpp"
#include "Nenuphar/Rendering/GraphicsContext.hpp"
#include "Nenuphar/Rendering/RenderDevice.hpp"

namespace Np = Nenuphar;


class GenesisApp : public Np::AppDelegate
{
public:
    virtual Np::AppContext* ProvideAppContext() override;

    virtual Bool OnInitialize() override;

    virtual void OnTick(Double deltaTime) override;

    virtual void OnClose() override;

public:
    GenesisApp();
    ~GenesisApp() = default;

private:
    Np::Model Cube;
    Np::AppContext Context;
    Np::EntityRegistry Registry;
    Np::Entity ECamera;
    Np::Entity ESponza;
    SharedRef<Np::RenderDevice> Device;
    SharedRef<Np::Window> MainWindow;
    RenderData MainRenderData;
};
