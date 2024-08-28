#include "Nenuphar/Rendering/OpenGL/OpenGLTexture.hpp"
#include "Nenuphar/Common/Debug/Debug.hpp"
#include "Nenuphar/Core/Logger/Logger.hpp"
#include "Nenuphar/Rendering/OpenGL/OpenGLDebugger.hpp"
#include "Nenuphar/Rendering/Texture.hpp"

namespace Nenuphar
{

    OpenGLTextureStorage OpenGLTextureStorage::s_mainStorage;

    
    OpenGLTextureStorage::TStorageTexture2D& OpenGLTextureStorage::GetGlobalStorageTexture2D()
    {
        return OpenGLTextureStorage::s_mainStorage.m_storageTexture2D;
    }

    
    OpenGLFormatPixel OpenGLInternalFormat(const TextureInformation& info)
    {
        switch (info.Format)
        {
            case ImageFormat::RGB:
                return OpenGLFormatPixel::RGB;
            case ImageFormat::RGBA:
                return OpenGLFormatPixel::RGBA;
            case ImageFormat::RED:
                return OpenGLFormatPixel::RED;
            default:
                CCHECK(false)
        }
    }

    
    void TexImage2D(UInt target, Int level, const TextureInformation& info)
    {
        OpenGLFormatPixel format = OpenGLInternalFormat(info);
        NPOGL_CHECK_CALL(glTexImage2D(
                target,
                level,
                format,
                info.Width,
                info.Height,
                0,
                format,
                GL_UNSIGNED_BYTE,
                info.Data));
    }

    
	void GenerateMipmap(UInt target) 
	{
		NPOGL_CHECK_CALL(glGenerateMipmap(target));
    }

    
	void ActiveTexture(UInt slot)
	{
		NPOGL_CHECK_CALL(glActiveTexture(GL_TEXTURE0 + slot));
    }

    
    void DefaultParameterTexture(const TextureInformation& dataImage,
                                 OpenGLTexture<Texture2D>::Parameter parameter)
	{
        parameter
                .WithParameter(GL_TEXTURE_WRAP_T, GL_REPEAT)
                .WithParameter(GL_TEXTURE_WRAP_S, GL_REPEAT)
                .WithParameter(GL_TEXTURE_MIN_FILTER, GL_LINEAR)
                .WithParameter(GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        TexImage2D(GL_TEXTURE_2D, 0, dataImage);
        GenerateMipmap(GL_TEXTURE_2D);
    }

}

