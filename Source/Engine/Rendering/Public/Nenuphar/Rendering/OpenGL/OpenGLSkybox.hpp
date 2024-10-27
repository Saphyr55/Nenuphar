#pragma once

#include "Nenuphar/Common/Type/Type.hpp"
#include "Nenuphar/Rendering/OpenGL/OpenGLTexture.hpp"
#include "Nenuphar/Rendering/RenderHandle.hpp"
#include "Nenuphar/Rendering/Skybox.hpp"

#include <glad/glad.h>

namespace Nenuphar
{
    class RenderDevice;
    class ImageAsset;

    class OpenGLSkybox : public Skybox
    {
    public:
        static SharedRef<OpenGLSkybox> Create(const std::array<SharedRef<ImageAsset>, 6>& assets, RenderDevice* device);

        void BindTextureUnit(OpenGLTextureUnit unit);

        void Destroy() override;

        void Initialize(const std::array<SharedRef<ImageAsset>, 6>& assets, RenderDevice* device);

        inline SharedRef<RenderHandle> GetRenderHandle() { return m_renderHandle; }

        inline UInt GetTextureHandle() { return m_textureHandle; }        

        inline UInt GetCount() { return m_count; }

    private:
        SharedRef<RenderHandle> m_renderHandle = nullptr;
        UInt m_textureHandle = GL_INVALID_INDEX;
        UInt m_count = GL_INVALID_VALUE;
    };

}