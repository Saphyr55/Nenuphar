#include "Noname/Noname.hpp"
#include "Nenuphar/ApplicationCore.hpp"
#include "Nenuphar/Core.hpp"
#include "Nenuphar/EventSystem.hpp"

namespace Np = Nenuphar;

NPDefineAddress(PrintSomethingAddr, "My.Address.Print-Something")

struct MEvent
{
    Np::String Name;
};

Np::Int main()
{
    auto Application = Np::Application::CreateApplication();

    auto& WindowEventHandler = Application->GetWindowEventHandler();
    auto& EventBus = Application->GetEventBus();

    WindowEventHandler.OnMouseMove(EventBus, [](auto& Event)
    {
        NP_DEBUG(NonameApplication, "{}", Event.PosX);
    });

    auto Window = Application->CreateApplicationWindow
    ({
        .PosX = 0,
        .PosY = 0,

        .Width = 1080,
        .Height = 720,

        .Title = "Nenuphar.Window",
    });

    Window->Show();

    while (Application->IsRunning())
    {

        Window->PoolEvent();
    }

    return 0;
}
