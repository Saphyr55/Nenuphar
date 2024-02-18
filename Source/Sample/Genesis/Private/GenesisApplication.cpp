#include "Genesis/GenesisApplication.hpp"

#include <Nenuphar/Core.hpp>
#include <Nenuphar/EventSystem.hpp>

using namespace Nenuphar;

GenesisApplication::GenesisApplication()
    : window(MakeSharedRef<Window>(GDefaultWindowDefinition))
{
}


void GenesisApplication::Setup()
{
    EntryApplication::Setup();

    NP_INFO(GenesisApplication, "Setup Genesis Entry Application.");

    window->GetWindowEventHandler()
        .OnClose(GetEventBus(), [&](auto&)
        {
            EntryApplication::Stop();
        });

    window->GetWindowEventHandler()
        .OnButtonPressed(GetEventBus(), [](MouseButtonEvent e)
        {
            if (e.Button == Input::Button::Right)
            {
                NP_DEBUG(Main, "Pressed Button Right. {}", static_cast<Int>(e.Button));
            }
        });

    window->Show();
}

void GenesisApplication::Update(const Float deltaTime)
{
    EntryApplication::Update(deltaTime);

    window->PoolEvent();
}


void GenesisApplication::Stop()
{
    EntryApplication::Stop();
}

bool GenesisApplication::IsRunning()
{
    return EntryApplication::IsRunning();
}

void GenesisApplication::Destroy() const
{
    EntryApplication::Destroy();
}

EventBus& GenesisApplication::GetEventBus()
{
    return EntryApplication::GetEventBus();
}
