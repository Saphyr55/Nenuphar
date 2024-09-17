#pragma once

#include "Nenuphar/Common/Type/Type.hpp"

namespace Nenuphar 
{

    struct RenderFrameDefinition
    {
        Int X;
        Int Y;
        Int Width;
        Int Height;
    };

    class RenderFrame
    {
    public:
        SharedRef<RenderFrame> CreateRenderFrame(const RenderFrameDefinition& definition);

        virtual void BeginFrame() = 0;
        
        virtual void EndFrame() = 0;
    };
    

}