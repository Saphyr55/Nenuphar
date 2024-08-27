#pragma once

#include "Nenuphar/Common/Instanciate.hpp"
#include "Nenuphar/Common/Type/Type.hpp"
#include "Nenuphar/Core/IO/Path.hpp"
#include "Nenuphar/Resource/Resource.hpp"
#include "Nenuphar/Rendering/OpenGL/OpenGL.hpp"
#include "Nenuphar/Rendering/OpenGL/OpenGLDebugger.hpp"
#include "Nenuphar/Rendering/OpenGL/OpenGLTexture.hpp"
#include "Nenuphar/Rendering/Texture.hpp"
#include "glad/glad.h"
#include <cstddef>
#include <memory>


namespace Nenuphar
{

    /**
     *
     */
    void TexImage2D(UInt target, Int level, const TextureInformation& dataImage);

    
    /**
     *
     */
    void GenerateMipmap(UInt target);

    
    /**
     *
     */
    void ActiveTexture(UInt slot);


    /**
     *
     */
    template<OpenGLTextureTarget target>
    void OpenGLBindTexture(const TextureIdentication& identication)
    {
        NPOGL_CHECK_CALL(glBindTexture(target, identication.Handle));
    }

    
    /**
     *
     */
    template<OpenGLTextureTarget target>
    void OpenGLUnbindTexture()
    {
        NPOGL_CHECK_CALL(glBindTexture(target, 0));
    }

    
    /**
     *
     */
    template<OpenGLTextureTarget target>
    class OpenGLTexture
	{
    public:
        
		struct Parameter
    	{
            auto WithParameter(UInt pName, Int param) const
                    -> const Parameter&;
            
            auto WithParameter(UInt pName, Float param) const
                    -> const Parameter&;
            
            auto WithParameter(UInt pName, const Int* param) const
                    -> const Parameter&;
            
            auto WithParameter(UInt pName, const Float* param) const
                    -> const Parameter&;
		};

        using TOnCreateTexture =
                std::function<void(const TextureInformation&,
                                   const Parameter&)>;

        
        void Bind() const;

        void Unbind() const;

        inline Texture GetHandle() const
        {
            return m_identification.Handle;
        }

        inline TextureUnit GetUnit() const
        {
            return m_identification.Unit;
        }
        
        inline const TextureIdentication& GetTextureIdentication() const
        {
            return m_identification;
        }

        inline TextureIdentication& GetTextureIdentication()
        {
            return m_identification;
        }

        static SharedRef<OpenGLTexture<target>> LoadFromImage(
                const Path& path, const TOnCreateTexture& onCreate);

        OpenGLTexture(TextureUnit unit);
        ~OpenGLTexture();

    private:
        TextureIdentication m_identification;
    };

    
    /**
     *
     */
    using OpenGLTexture2D = OpenGLTexture<OpenGLTextureTarget::Texture2D>;

    
    // TODO: Use a sparse set and the pagination technique to have better perfomance.
    class OpenGLTextureStorage
    {
    public:
        template<OpenGLTextureTarget target>
        using TStorage = std::unordered_map<Texture, SharedRef<OpenGLTexture<target>>>;

        using TStorageTexture2D = TStorage<OpenGLTextureTarget::Texture2D>;

        static TStorage<OpenGLTextureTarget::Texture2D>& GetGlobalStorageTexture2D();

    private:
        TStorageTexture2D m_storageTexture2D;
        static OpenGLTextureStorage s_mainStorage;
    };


    /**
     *
     */
    void DefaultParameterTexture(const TextureInformation& dataImage,
                                 OpenGLTexture<Texture2D>::Parameter parameter);

    
    /**
     *
     */
    template<OpenGLTextureTarget target>
    SharedRef<OpenGLTexture<target>> CreateOpenGLTexture(TextureUnit unit)
    {
        auto glTexture = MakeSharedRef<OpenGLTexture<target>>(unit);
        OpenGLTextureStorage::GetGlobalStorageTexture2D()
                .insert({glTexture->GetHandle(), glTexture});
        
        return glTexture;
    }

    
    /**
     *
     */
    template<OpenGLTextureTarget target>
    OpenGLTexture<target>::OpenGLTexture(TextureUnit unit)
    {
        m_identification.Unit = unit;
        NPOGL_CHECK_CALL(glGenTextures(1, &m_identification.Handle));
        Bind();
    }


    /**
     *
     */
    template<OpenGLTextureTarget target>
    OpenGLTexture<target>::~OpenGLTexture()
    {
        // TODO: Remove this texture from the corresponding storage.
    }


    /**
     *
     */
    template<OpenGLTextureTarget target>
    void OpenGLTexture<target>::Bind() const
    {
        OpenGLBindTexture<target>(m_identification);
    }


    /**
     *
     */
    template<OpenGLTextureTarget target>
	void OpenGLTexture<target>::Unbind() const
	{
        OpenGLUnbindTexture<target>();
    }

    
    /**
     *
     */
    template<OpenGLTextureTarget target>
    auto OpenGLTexture<target>::Parameter::WithParameter(UInt pName, Int param)
            const -> const Parameter&
    {
        NPOGL_CHECK_CALL(glTexParameteri(target, pName, param));
        return *this;
    }

    
    /**
     *
     */
    template<OpenGLTextureTarget target>
    auto OpenGLTexture<target>::Parameter::WithParameter(UInt pName, Float param)
            const -> const Parameter&
    {
		NPOGL_CHECK_CALL(glTexParameterf(target, pName, param));
		return *this;
    }

    
    /**
     *
     */
    template<OpenGLTextureTarget target>
    auto OpenGLTexture<target>::Parameter::WithParameter(UInt pName, const Int* param)
            const -> const Parameter&
    {
		NPOGL_CHECK_CALL(glTexParameteriv(target, pName, param));
		return *this;
    }


    /**
     *
     */
    template<OpenGLTextureTarget target>
    auto OpenGLTexture<target>::Parameter::WithParameter(UInt pName, const Float* param)
            const -> const Parameter&
    {
		NPOGL_CHECK_CALL(glTexParameterfv(target, pName, param));
		return *this;
    }


    /**
     *
     */
    template<OpenGLTextureTarget target>
    SharedRef<OpenGLTexture<target>>
    OpenGLTexture<target>::LoadFromImage(const Path& path,
                                         const TOnCreateTexture& onCreate)
	{
        auto texture = CreateOpenGLTexture<target>(0);

        auto bindedOnCreate = [&](const TextureInformation& info) {
            onCreate(info, Parameter());
        };

        texture->Bind();

        if (!LoadDataImage(path, bindedOnCreate))
        {
            texture = nullptr;
        }

        texture->Unbind();

        return texture;
    }


}
