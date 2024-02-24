#include "Nenuphar/ApplicationCore/Window.hpp"
#include "Nenuphar/Core/Engine.hpp"
#include "Nenuphar/EventSystem/WindowEventHandler.hpp"

using namespace Nenuphar;

void Update(Window& window)
{
    window.PoolEvent();
}

int main(const int ArgumentCount, char* ArgumentValues[])
{

    GEngine->Initialize(ArgumentCount, ArgumentValues);

    auto mainWindow = Window("Genisis Application", 1080, 720);
    auto& windowEventHandler = mainWindow.GetWindowEventHandler();

    windowEventHandler.OnClose([&](auto&)
    {
        mainWindow.Destroy();
        GIsFinish = true;
    });

    mainWindow.Show();

    return GEngine->Start(Partial(Update, mainWindow));
}
