#pragma once

#include "Nenuphar/Common/Common.hpp"
#include "Nenuphar/Graphics/OpenGL/OpenGL.hpp"

namespace Nenuphar
{

	template<OpenGLTextureTarget target>
	class Texture;

	struct DataImage
	{
		Word8* Data;
        Int Format;
		Int Width;
		Int Height;
	};

    template<OpenGLTextureTarget target>
    class Texture
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

		static Texture<target> LoadFromImage(std::string_view path, const std::function<void(const DataImage&, Parameter)>&);

        Texture();

    private:
        UInt texture{};
    };
	
	template<OpenGLTextureTarget target>
	void Texture<target>::Bind() const
	{
		glBindTexture(target, texture);
	}

	template<OpenGLTextureTarget target>
	void Texture<target>::Unbind() const
	{
		glBindTexture(target, 0);
	}

	template<OpenGLTextureTarget target>
	Texture<target>::Texture()
	{
		glGenTextures(1, &texture);
		Bind();
	}

	void LoadDataImage(std::string_view path, const std::function<void(const DataImage&)>&);

	void TexImage2D(UInt target, Int level, const DataImage& dataImage);

	void GenerateMipmap(UInt target);

	void ActiveTexture(UInt slot);

    void DefaultParameterTexture(const DataImage& dataImage, Texture<Texture2D>::Parameter parameter);

    template<OpenGLTextureTarget target>
	auto Texture<target>::Parameter::WithParameter(UInt pName, Int param) const -> const Parameter&
    {
		glTexParameteri(target, pName, param);
		return *this;
	}

	template<OpenGLTextureTarget target>
	auto Texture<target>::Parameter::WithParameter(UInt pName, Float param) const -> const Parameter&
    {
		glTexParameterf(target, pName, param);
		return *this;
	}

	template<OpenGLTextureTarget target>
	auto Texture<target>::Parameter::WithParameter(UInt pName, const Int* param) const -> const Parameter&
    {
		glTexParameteriv(target, pName, param);
		return *this;
	}

	template<OpenGLTextureTarget target>
	auto Texture<target>::Parameter::WithParameter(UInt pName, const Float* param) const -> const Parameter&
    {
		glTexParameterfv(target, pName, param);
		return *this;
	}

	template<OpenGLTextureTarget target>
	Texture<target> Texture<target>::LoadFromImage(std::string_view path, const std::function<void(const DataImage&, Texture::Parameter)>& f)
	{
		Texture<target> texture;
		texture.Bind();
		LoadDataImage(path, std::bind(f, std::placeholders::_1, Texture::Parameter()));
		texture.Unbind();
		return texture;
	}

	using Texture2d = Texture<OpenGLTextureTarget::Texture2D>;

}
