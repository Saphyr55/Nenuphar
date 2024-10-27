#include "Nenuphar/Rendering/OpenGL/OpenGLSkybox.hpp"
#include "Nenuphar/Common/Instanciate.hpp"
#include "Nenuphar/Common/Type/Type.hpp"
#include "Nenuphar/Core/Debug.hpp"
#include "Nenuphar/Rendering/ImageAsset.hpp"
#include "Nenuphar/Rendering/OpenGL/OpenGLDebugger.hpp"
#include "Nenuphar/Rendering/OpenGL/OpenGLTexture.hpp"
#include "Nenuphar/Rendering/RenderDevice.hpp"
#include "glad/glad.h"

namespace Nenuphar
{

    const std::vector<Vertex> GSkyboxVertices =
            {
                    //   Coordinates
                    Vertex(Vector3f(-1.0f, -1.0f, 1.0f)), //        7--------6
                    Vertex(Vector3f(1.0f, -1.0f, 1.0f)),  //       /|       /|
                    Vertex(Vector3f(1.0f, -1.0f, -1.0f)), //      4--------5 |
                    Vertex(Vector3f(-1.0f, -1.0f, -1.0f)),//      | |      | |
                    Vertex(Vector3f(-1.0f, 1.0f, 1.0f)),  //      | 3------|-2
                    Vertex(Vector3f(1.0f, 1.0f, 1.0f)),   //      |/       |/
                    Vertex(Vector3f(1.0f, 1.0f, -1.0f)),  //      0--------1
                    Vertex(Vector3f(-1.0f, 1.0f, -1.0f))};

    const std::vector<UInt> GSkyboxIndices =
            {
                    // Right
                    1, 2, 6,
                    6, 5, 1,
                    // Left
                    0, 4, 7,
                    7, 3, 0,
                    // Top
                    4, 5, 6,
                    6, 7, 4,
                    // Bottom
                    0, 3, 2,
                    2, 1, 0,
                    // Back
                    0, 1, 5,
                    5, 4, 0,
                    // Front
                    3, 7, 6,
                    6, 2, 3};
    
    SharedRef<OpenGLSkybox> OpenGLSkybox::Create(const std::array<SharedRef<ImageAsset>, 6>& assets, RenderDevice* device)
    {   
        SharedRef<OpenGLSkybox> skybox = MakeSharedRef<OpenGLSkybox>();
        skybox->Initialize(assets, device);
        return skybox;
    }

    void OpenGLSkybox::BindTextureUnit(OpenGLTextureUnit unit)
    {
        NP_GL_CHECK_CALL(glBindTextureUnit(unit, m_textureHandle));
    }

    void OpenGLSkybox::Destroy()
    {
        NP_GL_CHECK_CALL(glDeleteTextures(1, &m_textureHandle))
        m_renderHandle->Destroy();
    }

    void OpenGLSkybox::Initialize(const std::array<SharedRef<ImageAsset>, 6>& assets, RenderDevice* device)
    {
        NCHECK(assets.front())

        m_renderHandle = device->CreateRenderHandle(GSkyboxVertices, GSkyboxIndices);
        m_count = GSkyboxIndices.size();

        NP_GL_CHECK_CALL(glPixelStorei(GL_UNPACK_ALIGNMENT, 1));

        UInt w = assets.at(0)->Definition.Width;
        UInt h = assets.at(0)->Definition.Height;
        GLenum storageFormat = OpenGLTextureStorageFormat(assets.at(0)->Definition.Format);
        
        NP_GL_CHECK_CALL(glCreateTextures(GL_TEXTURE_CUBE_MAP, 1, &m_textureHandle))
        NP_GL_CHECK_CALL(glTextureStorage2D(m_textureHandle, 1, storageFormat, w, h));

        for (int face = 0; face < 6; face++)
        {
            SharedRef<ImageAsset> asset = assets.at(face);
            NCHECK(asset)

            GLenum format = OpenGLImageFormat(asset->Definition.Format);
            OpenGLTexture::Rect rect;
            rect.X = 0;
            rect.Y = 0;
            rect.Width = asset->Definition.Width;
            rect.Height = asset->Definition.Height;
            
            glTextureSubImage3D(
                    m_textureHandle,
                    0,
                    rect.X,
                    rect.Y,
                    face,
                    rect.Width,
                    rect.Height,
                    1,
                    format,
                    GL_UNSIGNED_BYTE,
                    asset->Definition.Data);
        }

        NP_GL_CHECK_CALL(glGenerateTextureMipmap(m_textureHandle));
        NP_GL_CHECK_CALL(glTextureParameteri(m_textureHandle, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
        NP_GL_CHECK_CALL(glTextureParameteri(m_textureHandle, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));
        NP_GL_CHECK_CALL(glTextureParameteri(m_textureHandle, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE));
        NP_GL_CHECK_CALL(glTextureParameteri(m_textureHandle, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
        NP_GL_CHECK_CALL(glTextureParameteri(m_textureHandle, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR));
    }

}// namespace Nenuphar