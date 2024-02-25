#pragma once

#pragma comment (lib, "opengl32.lib")

#ifdef NP_PLATFORM_WINDOWS
    #include <glad/glad_wgl.h>
#endif
#include <glad/glad.h>

#include "Nenuphar/Common/Common.hpp"

namespace Nenuphar
{
    
    enum OpenGLFormatPixel : Int
	{
		RGBA = GL_RGBA,
		RGB = GL_RGB,
        RED = GL_RED
	};

	enum OpenGLTextureTarget : UInt
	{
		Texture1D = GL_TEXTURE_1D,
		Texture2D = GL_TEXTURE_2D,
		Texture1DArray = GL_TEXTURE_1D_ARRAY,
		Texture2DArray = GL_TEXTURE_2D_ARRAY,
		Texture2DMultisample = GL_TEXTURE_2D_MULTISAMPLE,
		Texture2DMultisampleArray = GL_TEXTURE_2D_MULTISAMPLE_ARRAY,
		Texture3D = GL_TEXTURE_3D,
		TextureCubeMap = GL_TEXTURE_CUBE_MAP,
		TextureCubeMapArray = GL_TEXTURE_CUBE_MAP_ARRAY,
		TextureRectangle = GL_TEXTURE_RECTANGLE
	};

	enum OpenGLBufferTarget : Int
	{
		ArrayBuffer = GL_ARRAY_BUFFER,
		ElementArrayBuffer = GL_ELEMENT_ARRAY_BUFFER,
		UniformBuffer = GL_UNIFORM_BUFFER,
	};

	enum OpenGLBufferUsage : UInt
	{
		StreamDraw = GL_STREAM_DRAW,
		StreamRead = GL_STREAM_READ,
		StreamCopy = GL_STREAM_COPY,
		StaticDraw = GL_STATIC_READ,
		StaticRead = GL_STATIC_DRAW,
		StaticCopy = GL_STATIC_COPY,
		DynamicDraw = GL_DYNAMIC_READ,
		DynamicRead = GL_DYNAMIC_DRAW,
		DynamicCopy = GL_DYNAMIC_COPY,
	};

	enum OpenGLBufferMask : UInt
	{
		ColorBuffer = GL_COLOR_BUFFER_BIT,
		DepthBuffer = GL_DEPTH_BUFFER_BIT,
		StencilBuffer = GL_STENCIL_BUFFER_BIT,
	};

}
