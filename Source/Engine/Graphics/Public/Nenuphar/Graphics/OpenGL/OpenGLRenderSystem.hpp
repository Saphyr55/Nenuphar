#pragma once

#include "Nenuphar/Graphics/RenderSystem.hpp"

namespace Nenuphar
{

    struct OpenGLRenderSystem : RenderSystem
    {

        void Enable() override;

        void Clear() override;

    };

}