#include "Nenuphar/Rendering/OpenGL/OpenGLRenderDevice.hpp"

#include "Nenuphar/Common/Instanciate.hpp"
#include "Nenuphar/Common/Type/Type.hpp"
#include "Nenuphar/Rendering/OpenGL/OpenGLCommandBuffer.hpp"
#include "Nenuphar/Rendering/OpenGL/OpenGLCommandQueue.hpp"
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

    SharedRef<RenderHandle> OpenGLRenderDevice::CreateRenderHandle(const std::vector<Vertex>& vertices,
                                               const std::vector<VIndice>& indices)
    {
        auto vbo = OpenGLImmutableBuffer::Create(vertices);
        auto ebo = OpenGLImmutableBuffer::Create(indices);
        auto vao = OpenGLVertexArray::Create(ebo->GetHandle(),
                                             vbo->GetHandle());

        vbo->Destroy();
        ebo->Destroy();

        return vao;
    }

    SharedRef<CommandBuffer> OpenGLRenderDevice::CreateCommandBuffer()
    {
        return MakeSharedRef<OpenGLCommandBuffer>();
    }

    SharedRef<CommandQueue> OpenGLRenderDevice::CreateCommandQueue()
    {
        return MakeSharedRef<OpenGLCommandQueue>();
    }

    SharedRef<Texture> OpenGLRenderDevice::CreateTexture(SharedRef<ImageAsset> asset,
                                                         const TextureConstructOptions& option)
    {
        NCHECK(asset)

        OpenGLTexture::Rect rect;
        rect.X = 0;
        rect.Y = 0;
        rect.Width = asset->Definition.Width;
        rect.Height = asset->Definition.Height;

        SharedRef<OpenGLTexture> texture = OpenGLTexture::Create(asset->Definition, rect);

        if (option.AutoRelease)
        {
            option.Registry.Unload(asset);
        }

        return texture;
    }

    SharedRef<MainShaderProgram> OpenGLRenderDevice::GetMainShaderProgram()
    {
        return m_mainShaderProgram;
    }

    OpenGLRenderDevice::OpenGLRenderDevice(RenderAPI renderAPI, SharedRef<Window> window)
        : RenderDevice(renderAPI, window)
    {
        m_mainShaderProgram = MakeSharedRef<OpenGLMainShaderProgram>();
        m_mainShaderProgram->Initialize();
    }

    OpenGLRenderDevice::~OpenGLRenderDevice() = default;

}// namespace Nenuphar