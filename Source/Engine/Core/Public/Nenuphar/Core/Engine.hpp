#pragma once

#include <functional>

#include "Nenuphar/Common/Instanciate.hpp"
#include "Nenuphar/Common/Type/Type.hpp"

namespace Nenuphar
{

    class Engine final
    {
    public:
        void Initialize(int argc, const char** argv);

        static int Start(const std::function<void()>& runnable);

    };

    inline Bool GIsFinish = false;
    const inline Ptr<Engine> GEngine = MakeUnique<Engine>();

}
