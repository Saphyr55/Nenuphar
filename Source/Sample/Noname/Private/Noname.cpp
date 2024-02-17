#include "Noname/Noname.hpp"
#include "Dramatic/ApplicationCore/Window.hpp"
#include "Dramatic/ApplicationCore/Windows/WindowsWindow.hpp"
#include "Dramatic/Core.hpp"
#include "Dramatic/Common/Logger/Logger.hpp"

using namespace Dramatic;

int main()
{

    auto Application = std::make_unique<WindowsApplication>();

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
