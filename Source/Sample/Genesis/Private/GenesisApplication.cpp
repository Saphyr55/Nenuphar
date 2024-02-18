#include "Genesis/GenesisApplication.hpp"

#include <Nenuphar/ApplicationCore.hpp>
#include <Nenuphar/Core.hpp>
#include <Nenuphar/EventSystem.hpp>
#include <Nenuphar/Common.hpp>

using namespace Nenuphar;

void GenesisApplication::Initialize()
{
    EntryApplication::Initialize();

    NP_INFO(GenesisApplication, "Initialize Genesis Entry Application.");
    /*
    mainWindow->GetWindowEventHandler()
        .OnClose(GetEventBus(), [&](auto&) { Stop(); });

    mainWindow->GetWindowEventHandler()
        .OnButtonPressed(GetEventBus(), [](MouseButtonEvent e)
        {
            if (e.Button == Input::Button::Right)
            {
                NP_DEBUG(Main, "Pressed Button Right. {}", static_cast<Int>(e.Button));
            }
        });

    mainWindow->Show();
    */
}

void GenesisApplication::Update(const Float deltaTime)
{
    EntryApplication::Update(deltaTime);
    //mainWindow->PoolEvent();
}
