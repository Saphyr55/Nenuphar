#include "Nenuphar/Rendering/OpenGL/OpenGLRenderDevice.hpp"

#include "Nenuphar/Common/Instanciate.hpp"
#include "Nenuphar/Common/Type/Type.hpp"
#include "Nenuphar/Rendering/OpenGL/OpenGLBuffer.hpp"
#include "Nenuphar/Rendering/OpenGL/OpenGLCommandBuffer.hpp"
#include "Nenuphar/Rendering/OpenGL/OpenGLCommandQueue.hpp"
#include "Nenuphar/Rendering/OpenGL/OpenGLDebugger.hpp"
#include "Nenuphar/Rendering/OpenGL/OpenGLShader.hpp"
#include "Nenuphar/Rendering/OpenGL/OpenGLSkybox.hpp"
#include "Nenuphar/Rendering/OpenGL/OpenGLSkyboxShader.hpp"
#include "Nenuphar/Rendering/OpenGL/OpenGLTexture.hpp"
#include "Nenuphar/Rendering/OpenGL/OpenGLVertexArray.hpp"
#include "Nenuphar/Rendering/RenderDevice.hpp"
#include "Nenuphar/Rendering/Shader.hpp"
#include "Nenuphar/Rendering/Texture.hpp"

#include <glad/glad.h>


namespace Nenuphar
{

    void OpenGLRenderDevice::Enable()
    {
        NP_GL_CHECK_CALL(glEnable(GL_DEPTH_TEST))

        NP_GL_CHECK_CALL(glEnable(GL_BLEND))
        NP_GL_CHECK_CALL(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA))
        
        NP_GL_CHECK_CALL(glEnable(GL_CULL_FACE));
        NP_GL_CHECK_CALL(glCullFace(GL_FRONT));

        NP_GL_CHECK_CALL(glEnable(GL_TEXTURE_CUBE_MAP_SEAMLESS))
    }

    SharedRef<Shader> OpenGLRenderDevice::CreateShader(const ShaderConstructOptions& options)
    {
        return MakeSharedRef<OpenGLShader>(options.VertexSource, options.FragmentSource);
    }

    SharedRef<RenderHandle> OpenGLRenderDevice::CreateRenderHandle(
            const std::vector<Vertex>& vertices,
            const std::vector<VIndice>& indices)
    {   
        SharedRef<OpenGLImmutableBuffer> vbo = OpenGLImmutableBuffer::Create(vertices);
        SharedRef<OpenGLImmutableBuffer> ebo = OpenGLImmutableBuffer::Create(indices);
        SharedRef<OpenGLVertexArray> vao = OpenGLVertexArray::Create(vbo->GetHandle(), ebo->GetHandle());

        return vao;
    }

    SharedRef<CommandBuffer> OpenGLRenderDevice::CreateCommandBuffer()
    {
        return MakeSharedRef<OpenGLCommandBuffer>();
    }
    
    RenderCommand OpenGLRenderDevice::CreateProjectionViewCommand(const Matrix4f& projection, const Matrix4f& view)
    {
        return [&] {
            constexpr std::size_t offset = 0;
            constexpr std::size_t size = sizeof(MainUniformBlock);

            MainUniformBlock mainUniformBlock;
            mainUniformBlock.Projection = projection;
            mainUniformBlock.View = view;

            m_UMainUniformBlock = mainUniformBlock;

            m_mainUniformBuffer->Bind();
            m_mainUniformBuffer->BufferSubData(offset, size, &m_UMainUniformBlock);
            m_mainUniformBuffer->Unbind();
        };
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
    
    SharedRef<Skybox> OpenGLRenderDevice::CreateSkybox(const std::array<SharedRef<ImageAsset>, 6>& faces)
    {
        return OpenGLSkybox::Create(faces, this);
    }

    SharedRef<MaterialShaderProgram> OpenGLRenderDevice::GetMaterialShaderProgram()
    {
        return m_mainShaderProgram;
    }

    SharedRef<SkyboxShaderProgram> OpenGLRenderDevice::GetSkyboxShaderProgram()
    {
        return m_skyboxShaderProgram;
    }

    OpenGLRenderDevice::OpenGLRenderDevice(RenderAPI renderAPI, SharedRef<Window> window)
        : RenderDevice(renderAPI, window)
    {
        
        m_UMainUniformBlock = MainUniformBlock();

        m_mainShaderProgram = MakeSharedRef<OpenGLMaterialShaderProgram>();
        m_mainShaderProgram->Initialize();

        m_skyboxShaderProgram = MakeSharedRef<OpenGLSkyboxShaderProgram>();
        m_skyboxShaderProgram->Initialize();
    
        m_mainUniformBuffer = MakeSharedRef<OpenGLUniformBuffer>(sizeof(MainUniformBlock));
        m_mainUniformBuffer->BufferData(&m_UMainUniformBlock, OpenGLBufferUsage::StaticDraw);
        m_mainUniformBuffer->BindBufferBase(GMainBindingBlockIndex);
    }

    OpenGLRenderDevice::~OpenGLRenderDevice() = default;

}// namespace Nenuphar