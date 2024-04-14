#pragma once

#include "Nenuphar/Common/Common.hpp"
#include "Nenuphar/Core/Resource/Resource.hpp"
#include "Nenuphar/Rendering/OpenGL/OpenGL.hpp"

namespace Nenuphar
{

	template<OpenGLTextureTarget target>
	class OpenGLTexture;

	struct DataImage
	{
		Word8* Data;
        Int Format;
		Int Width;
		Int Height;
	};

    template<OpenGLTextureTarget target>
    class OpenGLTexture
	{
    public:
		struct Parameter
    	{
			auto WithParameter(UInt pName, Int param) const -> const Parameter&;
			auto WithParameter(UInt pName, Float param) const -> const Parameter&;
			auto WithParameter(UInt pName, const Int* param) const -> const Parameter&;
			auto WithParameter(UInt pName, const Float* param) const -> const Parameter&;
		};

        void Bind() const;
        void Unbind() const;

		explicit operator UInt() { return texture; }

		static OpenGLTexture<target> LoadFromImage(const Path& path, const std::function<void(const DataImage&, Parameter)>&);

        OpenGLTexture();

    private:
        UInt texture{};
    };

    template<OpenGLTextureTarget target>
    OpenGLTexture<target>::OpenGLTexture()
    {
        glGenTextures(1, &texture);
        Bind();
    }

    template<OpenGLTextureTarget target>
	void OpenGLTexture<target>::Bind() const
	{
		glBindTexture(target, texture);
	}

	template<OpenGLTextureTarget target>
	void OpenGLTexture<target>::Unbind() const
	{
		glBindTexture(target, 0);
	}

    void LoadDataImage(const Path& path, const std::function<void(const DataImage&)>& f);

	void TexImage2D(UInt target, Int level, const DataImage& dataImage);

	void GenerateMipmap(UInt target);

	void ActiveTexture(UInt slot);

    void DefaultParameterTexture(const DataImage& dataImage, OpenGLTexture<Texture2D>::Parameter parameter);

    template<OpenGLTextureTarget target>
	auto OpenGLTexture<target>::Parameter::WithParameter(UInt pName, Int param) const -> const Parameter&
    {
		glTexParameteri(target, pName, param);
		return *this;
	}

	template<OpenGLTextureTarget target>
	auto OpenGLTexture<target>::Parameter::WithParameter(UInt pName, Float param) const -> const Parameter&
    {
		glTexParameterf(target, pName, param);
		return *this;
	}

	template<OpenGLTextureTarget target>
	auto OpenGLTexture<target>::Parameter::WithParameter(UInt pName, const Int* param) const -> const Parameter&
    {
		glTexParameteriv(target, pName, param);
		return *this;
	}

	template<OpenGLTextureTarget target>
	auto OpenGLTexture<target>::Parameter::WithParameter(UInt pName, const Float* param) const -> const Parameter&
    {
		glTexParameterfv(target, pName, param);
		return *this;
	}

	template<OpenGLTextureTarget target>
    OpenGLTexture<target> OpenGLTexture<target>::LoadFromImage(const Path& path, const std::function<void(const DataImage&, OpenGLTexture::Parameter)>& f)
	{
        OpenGLTexture<target> texture;
		texture.Bind();
		LoadDataImage(path, std::bind(f, std::placeholders::_1, OpenGLTexture::Parameter()));
		texture.Unbind();
		return texture;
	}

	using OpenGLTexture2D = OpenGLTexture<OpenGLTextureTarget::Texture2D>;

}
