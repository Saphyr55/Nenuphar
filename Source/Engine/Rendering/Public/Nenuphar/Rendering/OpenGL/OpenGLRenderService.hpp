#pragma once

#include "Nenuphar/Common/Type/Type.hpp"
#include "Nenuphar/Math/Vector4.hpp"
#include "Nenuphar/Rendering/OpenGL/OpenGLRenderer.hpp"
#include "Nenuphar/Rendering/RenderService.hpp"

namespace Nenuphar
{

    class OpenGLRenderService : public RenderService
    {
    public:
        SharedRef<Renderer> GetRenderer() override;

        void Enable() const override;

        void Clear(const Vector4f& color) const override;

        OpenGLRenderService();
        ~OpenGLRenderService() override;

    private:
        SharedRef<OpenGLRenderer> m_renderer;
    };

}