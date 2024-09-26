#include "Nenuphar/Rendering/OpenGL/OpenGLTexture.hpp"
#include "Nenuphar/Common/Instanciate.hpp"
#include "Nenuphar/Common/Type/Type.hpp"
#include "Nenuphar/Core/Debug.hpp"
#include "Nenuphar/Rendering/OpenGL/OpenGLDebugger.hpp"
#include "glad/glad.h"

namespace Nenuphar
{

    SharedRef<OpenGLTexture> OpenGLTexture::Create(const ImageDefinition& imageDefinition,
                                                   const Rect& rect, const Int& level)
    {
        SharedRef<OpenGLTexture> texture = MakeSharedRef<OpenGLTexture>(imageDefinition);

        texture->Initialize();
        texture->SubImage(level, rect, imageDefinition.Data);

        texture->SetParameter(GL_TEXTURE_WRAP_T, GL_REPEAT);
        texture->SetParameter(GL_TEXTURE_WRAP_S, GL_REPEAT);
        texture->SetParameter(GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        texture->SetParameter(GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        NP_GL_CHECK_CALL(glGenerateTextureMipmap(texture->GetHandle()));

        return texture;
    }

    OpenGLTexture::OpenGLTexture(const ImageDefinition& imageDefinition)
        : m_imageDefinition(imageDefinition)
        , m_formatPixel(imageDefinition.Format)
    {
    }

    OpenGLTexture::~OpenGLTexture()
    {
    }

    void OpenGLTexture::Initialize()
    {
        UInt width = m_imageDefinition.Width;
        UInt height = m_imageDefinition.Height;

        NP_GL_CHECK_CALL(glCreateTextures(GL_TEXTURE_2D, 1, &m_handle))
        NP_GL_CHECK_CALL(glTextureStorage2D(m_handle, 1, OpenGLTextureStorageFormat(m_formatPixel), width, height))
    }

    void OpenGLTexture::Destroy()
    {
        NP_GL_CHECK_CALL(glDeleteTextures(1, &m_handle))
    }

    void OpenGLTexture::Bind() const
    {
        NP_GL_CHECK_CALL(glBindTexture(GL_TEXTURE_2D, m_handle));
    }

    void OpenGLTexture::SetParameter(UInt pName, Int param) const
    {
        NP_GL_CHECK_CALL(glTextureParameteri(m_handle, pName, param));
    }

    void OpenGLTexture::SetParameter(UInt pName, Float param) const
    {
        NP_GL_CHECK_CALL(glTextureParameterf(m_handle, pName, param));
    }

    void OpenGLTexture::SetParameter(UInt pName, const Int* param) const
    {
        NP_GL_CHECK_CALL(glTextureParameteriv(m_handle, pName, param));
    }

    void OpenGLTexture::SetParameter(UInt pName, const Float* param) const
    {
        NP_GL_CHECK_CALL(glTextureParameterfv(m_handle, pName, param));
    }

    void OpenGLTexture::SubImage(Int level, const Rect& rect, const void* pixels)
    {
        NP_GL_CHECK_CALL(
                glTextureSubImage2D(m_handle, 0,
                                    rect.X, rect.Y, rect.Width, rect.Height,
                                    OpenGLImageFormat(m_formatPixel), GL_UNSIGNED_BYTE, pixels));
    }

    void OpenGLTexture::BindTextureUnit(OpenGLTextureUnit unit)
    {
        NP_GL_CHECK_CALL(glBindTextureUnit(unit, m_handle));
    }

    void OpenGLUnbindTexture(OpenGLTextureTarget target)
    {
        NP_GL_CHECK_CALL(glBindTexture(target, 0));
    }

    GLenum OpenGLTextureStorageFormat(const ImageFormat& format)
    {
        switch (format)
        {
            case ImageFormat::RGB: {
                return GL_RGB8;
            }
            case ImageFormat::RGBA: {
                return GL_RGBA8;
            }
            case ImageFormat::RG: {
                return GL_RG8;
            }
            case ImageFormat::RED: {
                return GL_R8;
            }
        }
        NCHECK(false)
    }

    GLenum OpenGLImageFormat(const ImageFormat& format)
    {
        switch (format)
        {
            case ImageFormat::RGB: {
                return GL_RGB;
            }
            case ImageFormat::RGBA: {
                return GL_RGBA;
            }
            case ImageFormat::RG: {
                return GL_RG;
            }
            case ImageFormat::RED: {
                return GL_RED;
            }
        }
        NCHECK(false)
    }


}// namespace Nenuphar
