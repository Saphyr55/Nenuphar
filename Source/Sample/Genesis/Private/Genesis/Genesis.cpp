#include "Nenuphar/ApplicationCore/Window.hpp"
#include "Nenuphar/Core/Engine.hpp"
#include "Nenuphar/Assets/Assets.hpp"
#include "Nenuphar/EventSystem/WindowEventHandler.hpp"
#include "Nenuphar/Graphics/GraphicContext.hpp"

#include <glad/glad.h>

#include "Generated/Generated.hpp"

using namespace Nenuphar;

class OnReceiveEvent
{
public:
    void Receive(String data);

private:
    Signal<String> signal;
};

void OnReceiveEvent::Receive(String data)
{
    signal.Emit(std::move(data));
}


void Render(GraphicContext& graphicContext, Window& window)
{
    glClearColor(0.2, 0.2, 0.4, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    graphicContext.SwapBuffers();
}

int main(const int ArgumentCount, char* ArgumentValues[])
{

    GEngine->Initialize(ArgumentCount, ArgumentValues);

    String filepath = AssetsFolder::Path("/Shaders/MainFragment.glsl");
    Window window("Genesis Application", 1080, 720);

    auto graphicContext = GraphicContext::Create(window);

    auto& windowSignals = window.GetWindowSignals();

    windowSignals.OnClose().ConnectConn([&](auto&, auto&)
    {
        window.Destroy();
        GIsFinish = true;
    });

    windowSignals.OnResize().ConnectHandler([&](auto&)
    {
        Render(*graphicContext, window);
    });

    window.Show();

    return GEngine->Start([&]
    {
        Render(*graphicContext, window);
        window.PoolEvent();
    });
}
