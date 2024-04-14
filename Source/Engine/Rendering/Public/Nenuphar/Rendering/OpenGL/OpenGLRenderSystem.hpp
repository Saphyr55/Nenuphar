#pragma once

#include "Nenuphar/Rendering/RenderSystem.hpp"

namespace Nenuphar
{


    class OpenGLRenderSystem : public RenderSystem
    {
    public:
        void Enable() const override;

        void Clear(const Vector4f& color) const override;

    };

}