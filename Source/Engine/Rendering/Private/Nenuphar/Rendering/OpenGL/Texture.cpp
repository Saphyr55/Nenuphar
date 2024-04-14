#include "Nenuphar/Rendering/OpenGL/Texture.hpp"
#include "Nenuphar/Core/Logger/Logger.hpp"

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

namespace Nenuphar
{

	void TexImage2D(UInt target, Int level, const DataImage& dataImage)
	{
		glTexImage2D(target, level, GL_RGB, dataImage.Width, dataImage.Height, 0, dataImage.Format, GL_UNSIGNED_BYTE, dataImage.Data);
	}

	void GenerateMipmap(UInt target) 
	{
		glGenerateMipmap(target);
	}

	void ActiveTexture(UInt slot)
	{
		glActiveTexture(GL_TEXTURE0 + slot);
	}

    void DefaultParameterTexture(const DataImage& dataImage, OpenGLTexture<Texture2D>::Parameter parameter)
	{
        parameter
            .WithParameter(GL_TEXTURE_WRAP_T, GL_REPEAT)
            .WithParameter(GL_TEXTURE_WRAP_S, GL_REPEAT)
            .WithParameter(GL_TEXTURE_MIN_FILTER, GL_LINEAR)
            .WithParameter(GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        TexImage2D(GL_TEXTURE_2D, 0, dataImage);
        GenerateMipmap(GL_TEXTURE_2D);
    }

    void LoadDataImage(const Path& path, const std::function<void(const DataImage&)>& f)
	{

		DataImage dataImage{};
		stbi_set_flip_vertically_on_load(true);
		dataImage.Data = stbi_load
        (
            Path::FilePathData(path),
            &dataImage.Width, 
            &dataImage.Height, 
            &dataImage.Format, 
            0
        );

        if (!dataImage.Data)
        {
            NP_ERROR(LoadDataImage, "Cannot load '{}' image.\n", Path::FilePathData(path));
            return;
        }

		switch (dataImage.Format) 
        {
            case 4:
            {
                dataImage.Format = OpenGLFormatPixel::RGBA;
                break;
            }
            case 3:
            {
                dataImage.Format = OpenGLFormatPixel::RGB;
                break;
            }
            case 1:
            {
                dataImage.Format = OpenGLFormatPixel::RED;
                break;
            }
            default:
            {
                NP_ERROR(LoadDataImage, "Error Load Textures: Automatic Textures type recognition failed");
                throw std::exception();
            }
		}

		f(dataImage);

		stbi_image_free(dataImage.Data);
	}

}

