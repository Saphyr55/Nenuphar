#pragma once

#include "Nenuphar/Rendering/RenderSystem.hpp"

namespace Nenuphar
{

    struct OpenGLRenderSystem : RenderSystem
    {

        void Enable() override;

        void Clear() override;

    };

}