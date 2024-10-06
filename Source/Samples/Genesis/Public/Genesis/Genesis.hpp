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
#include "WindowEventHandler.hpp"

namespace Np = Nenuphar;


class GenesisApp : public Np::AppDelegate
{
public:
    virtual Np::AppContext* ProvideAppContext() override;

    virtual bool OnInitialize() override;

    virtual void OnTick(double deltaTime) override;

    virtual void OnClose() override;

    double GetDeltaTime();

public:
    GenesisApp();
    ~GenesisApp() = default;

private:
    double DeltaTime;
    Np::Model Cube;
    Np::AppContext Context;
    Np::EntityRegistry Registry;
    Np::Entity ECamera;
    Np::Entity ESponza;
    Np::SharedRef<WindowEventHandler> EventHandler;
    Np::SharedRef<Np::CommandQueue> CommandQueue;
    Np::SharedRef<Np::RenderDevice> Device;
    Np::SharedRef<Np::Window> MainWindow;
    RenderData MainRenderData;
};
