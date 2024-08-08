#include "Nenuphar/Core/Engine.hpp"

#include "Nenuphar/Core/Logger/Logger.hpp"

namespace Nenuphar
{

    Bool Engine::IsFinish = true;

    int Engine::LoopRun(const std::function<void()>& runnable)
    {
        try
        {
            NP_INFO(Engine::LoopRun, "Engine start the main loop.");
            IsFinish = false;

            while (!IsFinish)
            {
                runnable();
            }

            NP_INFO(Engine::LoopRun, "Engine closed the main loop.");
        }
        catch (const std::exception& e)
        {
            NP_CRITICAL(Engine::Start, "{}", e.what());
            return EXIT_FAILURE;
        }

        return EXIT_SUCCESS;
    }

}
