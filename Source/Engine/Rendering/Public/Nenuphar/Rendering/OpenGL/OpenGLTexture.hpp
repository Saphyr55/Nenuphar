#pragma once

#include "Nenuphar/Common/Type/Type.hpp"
#include "Nenuphar/Rendering/Image.hpp"
#include "Nenuphar/Rendering/OpenGL/OpenGL.hpp"
#include "Nenuphar/Rendering/Texture.hpp"


#include <glad/glad.h>


namespace Nenuphar
{

    using OpenGLTextureHandle = UInt;
    using OpenGLTextureUnit = UInt;

    /**
     * @brief 
     * 
     * @param info 
     * @return OpenGLFormatPixel 
     */
    GLenum OpenGLImageFormat(const ImageFormat& format);

    /**
     * @brief 
     * 
     * @param format 
     * @return GLenum 
     */
    GLenum OpenGLTextureStorageFormat(const ImageFormat& format);

    /**
     * @brief 
     * 
     * @param target 
     */
    void OpenGLUnbindTexture(OpenGLTextureTarget target);

    /**
     * @brief 
     * 
     */
    class OpenGLTexture : public Texture
    {
    public:
        struct Rect
        {
            Int X;
            Int Y;
            std::size_t Width;
            std::size_t Height;
        };

        static SharedRef<OpenGLTexture> Create(const ImageDefinition& imageDefinition,
                                               const Rect& rect, const Int& level = 0);

    public:
        void SetParameter(UInt pName, Int param) const;

        void SetParameter(UInt pName, Float param) const;

        void SetParameter(UInt pName, const Int* param) const;

        void SetParameter(UInt pName, const Float* param) const;

        void Initialize();

        void Destroy();

        void SubImage(Int level, const Rect& rect, const void* pixels);

        void BindTextureUnit(OpenGLTextureUnit unit);

        void Bind() const;

        inline OpenGLTextureHandle GetHandle() const
        {
            return m_handle;
        }

        OpenGLTexture(const ImageDefinition& imageDefinition);
        ~OpenGLTexture();

    private:
        ImageFormat m_formatPixel;
        OpenGLTextureHandle m_handle;
        ImageDefinition m_imageDefinition;
    };


}// namespace Nenuphar
