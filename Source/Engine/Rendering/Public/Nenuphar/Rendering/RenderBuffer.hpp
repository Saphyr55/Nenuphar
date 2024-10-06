#pragma once 

#include "RenderHandle.hpp"

namespace Nenuphar 
{

    class RenderBuffer : public RenderHandle
    {
    public:
        virtual void Destroy() = 0;
    };

}