#pragma once

#include <Nenuphar/Core.hpp>
#include <Nenuphar/ApplicationCore/EntryApplication.hpp>
#include <Nenuphar/ApplicationCore/Window.hpp>

using namespace Nenuphar;

class GenesisApplication final : EntryApplication
{

public:
    void Setup() override;

    void Update(Float deltaTime) override;

    GenesisApplication();

    ~GenesisApplication() override = default;

    void Stop() override;

    bool IsRunning() override;

    void Destroy() const override;

    EventBus& GetEventBus() override;

private:
    SharedRef<Window> window;
};

