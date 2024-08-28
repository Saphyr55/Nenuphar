#include "Genesis/Genesis.hpp"
#include "Nenuphar/Core/Engine.hpp"
#include "Nenuphar/Core/Logger/Logger.hpp"

using namespace Nenuphar;

int main(int argc, const char* argv[])
{
    GenesisApp app;
    NP_INFO(main, "Genesis application created.");

    app.OnInit();

    return Engine::LoopRun([&app] {
        app.OnUpdate();
        app.OnRender();
    });
}


