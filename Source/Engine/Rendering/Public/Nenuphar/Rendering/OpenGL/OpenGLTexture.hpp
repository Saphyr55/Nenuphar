#pragma once

#include "Nenuphar/Core/IO/Path.hpp"
#include "Nenuphar/Core/Resource/Resource.hpp"
#include "Nenuphar/Rendering/OpenGL/OpenGL.hpp"
#include "Nenuphar/Rendering/OpenGL/OpenGLDebugger.hpp"
#include "Nenuphar/Rendering/Texture.hpp"


namespace Nenuphar
{
	
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
		
		explicit operator Texture() { return texture; }

		static OpenGLTexture<target> LoadFromImage(const Path& path, const std::function<void(const TextureInformation&, Parameter)>&);

        OpenGLTexture();

    private:
        Texture texture;
    };

    /**
     *
     */
    using OpenGLTexture2D = OpenGLTexture<OpenGLTextureTarget::Texture2D>;

    /**
     *
     */
    class OpenGLRegistry
    {
    private:
        std::unordered_map<Texture, OpenGLTexture2D> m_registry;
    };

    /**
     *
     */
    template<OpenGLTextureTarget target>
    OpenGLTexture<target>::OpenGLTexture()
    {
        NPOGL_CHECK_CALL(glGenTextures(1, &texture));
        Bind();
    }

    template<OpenGLTextureTarget target>
	void OpenGLTexture<target>::Bind() const
	{
		NPOGL_CHECK_CALL(glBindTexture(target, texture));
    }

	template<OpenGLTextureTarget target>
	void OpenGLTexture<target>::Unbind() const
	{
		NPOGL_CHECK_CALL(glBindTexture(target, 0));
    }

    void LoadDataImage(const Path& path, const std::function<void(const TextureInformation&)>& f);

	void TexImage2D(UInt target, Int level, const TextureInformation& dataImage);

	void GenerateMipmap(UInt target);

	void ActiveTexture(UInt slot);

    void DefaultParameterTexture(const TextureInformation& dataImage, OpenGLTexture<Texture2D>::Parameter parameter);

    template<OpenGLTextureTarget target>
	auto OpenGLTexture<target>::Parameter::WithParameter(UInt pName, Int param) const -> const Parameter&
    {
        NPOGL_CHECK_CALL(glTexParameteri(target, pName, param));
        return *this;
    }

	template<OpenGLTextureTarget target>
	auto OpenGLTexture<target>::Parameter::WithParameter(UInt pName, Float param) const -> const Parameter&
    {
		NPOGL_CHECK_CALL(glTexParameterf(target, pName, param));
		return *this;
    }

	template<OpenGLTextureTarget target>
	auto OpenGLTexture<target>::Parameter::WithParameter(UInt pName, const Int* param) const -> const Parameter&
    {
		NPOGL_CHECK_CALL(glTexParameteriv(target, pName, param));
		return *this;
    }

	template<OpenGLTextureTarget target>
	auto OpenGLTexture<target>::Parameter::WithParameter(UInt pName, const Float* param) const -> const Parameter&
    {
		NPOGL_CHECK_CALL(glTexParameterfv(target, pName, param));
		return *this;
    }

	template<OpenGLTextureTarget target>
    OpenGLTexture<target> OpenGLTexture<target>::LoadFromImage(const Path& path, const std::function<void(const TextureInformation&, OpenGLTexture::Parameter)>& f)
	{
        OpenGLTexture<target> texture;
		texture.Bind();
		LoadDataImage(path, std::bind(f, std::placeholders::_1, OpenGLTexture::Parameter()));
		texture.Unbind();
		return texture;
	}


}
