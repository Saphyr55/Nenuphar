#pragma once

#include "Nenuphar/Rendering/RenderHandle.hpp"

namespace Nenuphar 
{
    class Framebuffer : public RenderHandle
    {
    public:
        virtual void Destroy() = 0;
    };
    
}