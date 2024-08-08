#include "Genesis/Genesis.hpp"
#include "Nenuphar/Core/Engine.hpp"
#include "Nenuphar/Core/Logger/Logger.hpp"

using namespace Nenuphar;

int main(int argc, const char* argv[])
{
    gn::GenesisApp app;
    NP_INFO(main, "Genesis application created.");

    app.Init();

    return Engine::LoopRun([&app]
    {
        app.Render();
    });
}


