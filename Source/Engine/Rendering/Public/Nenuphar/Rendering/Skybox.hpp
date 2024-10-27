#pragma once

#include "Nenuphar/Rendering/RenderHandle.hpp"

namespace Nenuphar 
{
    class Skybox : public RenderHandle
    {
    public:
        virtual void Destroy() = 0;
    };

}