#pragma once

#include <functional>

namespace Nenuphar
{

    class Engine
    {
    public:
        static int LoopRun(const std::function<void()>& runnable);

        static bool HasStarted;
        static bool IsFinish;
    };


}
