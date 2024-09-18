#pragma once

#include "Nenuphar/Common/Type/Type.hpp"
#include "Nenuphar/Rendering/Mesh.hpp"
#include "Nenuphar/Rendering/OpenGL/OpenGLMainShader.hpp"
#include "Nenuphar/Rendering/Renderer.hpp"
#include "Nenuphar/Rendering/Shader.hpp"

namespace Nenuphar
{

    class OpenGLRenderer : public Renderer
    {
    public:
        virtual SharedRef<MainShaderProgram> GetMainShaderProgram() override;

        virtual Texture PersistTexture(SharedRef<TextureAsset> asset,
                                       const PersitTextureOption& option = {}) const override;

        virtual ModelId PersistModel(const Model& model) const override;

        virtual MeshId PersistMesh(const Mesh& mesh) const override;

        virtual void TextureModel(const MeshId& model,
                                  const Texture& texture) const override;

        virtual void TextureMesh(const MeshId& mesh,
                                 const Texture& texture) const override;

        virtual void DrawModel(SharedRef<Shader> shader,
                               SharedRef<UniformRegistry> registry,
                               const ModelId& model) const override;
        
        virtual void DrawMesh(SharedRef<Shader> shader,
                              SharedRef<UniformRegistry> registry,
                              const MeshId& mesh) const override;

    public:
        OpenGLRenderer();
        virtual ~OpenGLRenderer() override = default;

    private:
        SharedRef<OpenGLMainShaderProgram> m_mainShaderProgram;
    };

}// namespace Nenuphar