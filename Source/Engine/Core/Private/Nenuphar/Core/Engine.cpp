#include "Nenuphar/Core/Engine.hpp"

#include "Nenuphar/Core/Logger/Logger.hpp"

namespace Nenuphar
{
    Bool Engine::HasStarted = false;
    Bool Engine::IsFinish = false;

    int Engine::LoopRun(const std::function<void()>& runnable)
    {
        try
        {
            NP_INFO(Engine::LoopRun, "Engine start the main loop.");
            IsFinish = false;
            HasStarted = true;

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
