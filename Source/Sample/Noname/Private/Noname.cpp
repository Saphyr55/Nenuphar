#include "Noname/Noname.hpp"
#include "Nenuphar/ApplicationCore/Window.hpp"
#include "Nenuphar/ApplicationCore/Windows/WindowsWindow.hpp"
#include "Nenuphar/Core.hpp"

namespace Np = Nenuphar;

int main()
{

    auto Application = std::make_unique<Np::WindowsApplication>();

    auto Window = Application->CreateApplicationWindow
    ({
        .PosX = 0,
        .PosY = 0,

        .Width = 1080,
        .Height = 720,

        .Title = "Dramatic Window",
    });

    Window->Show();

    while (Application->IsRunning())
    {
        Window->PoolEvent();
    }

    return 0;
}
