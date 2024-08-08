#pragma once

#include <concepts>
#include <functional>

#include "Nenuphar/Common/Instanciate.hpp"
#include "Nenuphar/Common/Type/Type.hpp"

namespace Nenuphar
{

    class Engine final
    {
    public:
        static int LoopRun(const std::function<void()>& runnable);

        static Bool IsFinish;
    };


}
