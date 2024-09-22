#pragma once

#include "Nenuphar/Common/Type/Type.hpp"
#include "Nenuphar/Rendering/OpenGL/OpenGL.hpp"
#include "Nenuphar/Rendering/Image.hpp"
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
    OpenGLFormatPixel OpenGLFormat(const ImageFormat& format);

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
        void SetParameter(UInt pName, Int param) const;

        void SetParameter(UInt pName, Float param) const;

        void SetParameter(UInt pName, const Int* param) const;

        void SetParameter(UInt pName, const Float* param) const;

    public:
        struct Rect
        {
            Int X;
            Int Y;
            std::size_t Width;
            std::size_t Height;
        };

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
        OpenGLFormatPixel m_formatPixel;
        OpenGLTextureHandle m_handle;
        ImageDefinition m_imageDefinition;
    };


}// namespace Nenuphar
