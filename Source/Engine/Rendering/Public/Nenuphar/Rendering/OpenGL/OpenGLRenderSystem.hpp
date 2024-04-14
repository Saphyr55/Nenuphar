#pragma once

#include "Nenuphar/Rendering/RenderSystem.hpp"

namespace Nenuphar
{

    class OpenGLRenderSystem : public RenderSystem
    {
    public:
        void Enable() const override;

        void Clear(const Vector4f& color) const override;

        TextureID MakeTexture2D(Path path) const override;

        void BindTexture(TextureID textureId) const override;

    };

}