#pragma once

#include "Nenuphar/Common/Instanciate.hpp"
#include "Nenuphar/Common/Type/Type.hpp"

namespace Nenuphar
{

    class RunnableEngineInterface;

    class Engine final
    {
    public:
        void Initialize(int argc, char** argv);

        int Start(RunnableEngineInterface& runnableEngine);
    };

    const inline Ptr<Engine> GEngine = MakeUnique<Engine>();

}
