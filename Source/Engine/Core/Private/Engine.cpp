#include "Nenuphar/Core/Engine.hpp"

#include "Nenuphar/ApplicationCore/Application.hpp"
#include "Nenuphar/Core/Logger/Logger.hpp"

namespace Nenuphar
{

    void Engine::Initialize(int argc, char** argv)
    {
    }

    int Engine::Start(const std::function<void()>& runnable)
    {
        try
        {
            while (!GIsFinish)
            {
                runnable();
            }
        }
        catch (const std::exception& e)
        {
            NP_CRITICAL(Engine::Start, "{}", e.what());
            return EXIT_FAILURE;
        }
        return EXIT_SUCCESS;
    }

}
