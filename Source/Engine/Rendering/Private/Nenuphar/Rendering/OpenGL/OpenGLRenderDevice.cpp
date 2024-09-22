#include "Nenuphar/Rendering/OpenGL/OpenGLRenderDevice.hpp"

#include "Nenuphar/Common/Instanciate.hpp"
#include "Nenuphar/Common/Type/Type.hpp"
#include "Nenuphar/Rendering/OpenGL/OpenGLCommandBuffer.hpp"
#include "Nenuphar/Rendering/OpenGL/OpenGLDebugger.hpp"
#include "Nenuphar/Rendering/OpenGL/OpenGLShader.hpp"
#include "Nenuphar/Rendering/OpenGL/OpenGLTexture.hpp"
#include "Nenuphar/Rendering/RenderDevice.hpp"
#include "Nenuphar/Rendering/Texture.hpp"

#include <glad/glad.h>


namespace Nenuphar
{

    void OpenGLRenderDevice::Enable()
    {
        NP_GL_CHECK_CALL(glEnable(GL_DEPTH_TEST));
        NP_GL_CHECK_CALL(glEnable(GL_BLEND));
        NP_GL_CHECK_CALL(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
    }

    SharedRef<Shader> OpenGLRenderDevice::CreateShader(const ShaderConstructOptions& options)
    {
        return MakeSharedRef<OpenGLShader>(options.VertexSource, options.FragmentSource);
    }

    SharedRef<CommandBuffer> OpenGLRenderDevice::CreateCommandBuffer()
    {
        return MakeSharedRef<OpenGLCommandBuffer>();
    }

    SharedRef<Texture> OpenGLRenderDevice::CreateTexture(SharedRef<ImageAsset> asset,
                                                         const SubmitTextureOption& option)
    {
        NCHECK(asset)
        SharedRef<OpenGLTexture> texture = MakeSharedRef<OpenGLTexture>(asset->Definition);
        texture->Initialize();

        OpenGLTexture::Rect rect;
        rect.X = 0;
        rect.Y = 0;
        rect.Width = asset->Definition.Width;
        rect.Height = asset->Definition.Height;
        texture->SubImage(0, rect, asset->Definition.Data);

        return texture;
    }

    OpenGLRenderDevice::OpenGLRenderDevice(RenderAPI renderAPI, SharedRef<Window> window)
        : RenderDevice(renderAPI, window)
    {
    }

    OpenGLRenderDevice::~OpenGLRenderDevice() = default;

}// namespace Nenuphar