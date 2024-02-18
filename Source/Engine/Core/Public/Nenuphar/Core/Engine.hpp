#pragma once

#include "Nenuphar/Common/Instanciate.hpp"
#include "Nenuphar/Common/Type/Type.hpp"

namespace Nenuphar
{

    class Engine final
    {
    public:
        void Initialize();

        void Store(const std::type_info& typeInfo);

        int Start();

        void Update(float dt);

        void Stop();
    };

    const inline Ptr<Engine> GEngine = MakeUnique<Engine>();

}
