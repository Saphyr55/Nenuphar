#pragma once

#include "Nenuphar/Rendering/Skybox.hpp"
#include "StanfordBunny/RenderData.hpp"

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


class StanfordBunnyApp : public Np::AppDelegate
{
public:
    virtual Np::AppContext* ProvideAppContext() override;

    virtual bool OnInitialize() override;

    virtual void OnTick(double deltaTime) override;

    virtual void OnClose() override;

    double GetDeltaTime();

public:
    StanfordBunnyApp();
    ~StanfordBunnyApp() = default;

private:
    double DeltaTime;
    Np::Model Cube;
    Np::AppContext Context;
    Np::EntityRegistry Registry;
    Np::Entity ECamera;
    Np::Entity EBunny;
    Np::SharedRef<Np::Skybox> Skybox;
    Np::SharedRef<WindowEventHandler> EventHandler;
    Np::SharedRef<Np::CommandQueue> CommandQueue;
    Np::SharedRef<Np::RenderDevice> Device;
    Np::SharedRef<Np::Window> MainWindow;
    RenderData MainRenderData;
};
