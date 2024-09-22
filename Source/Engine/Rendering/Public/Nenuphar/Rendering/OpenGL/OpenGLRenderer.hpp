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

        virtual Texture SubmitTexture(SharedRef<ImageAsset> asset,
                                      const SubmitTextureOption& option = {}) const override;

        virtual RenderObject SubmitRenderData(const std::vector<Vertex>& vertices,
                                              const std::vector<VIndice>& indices) const override;

        virtual void Render(RenderObject& object) const override;

    public:
        OpenGLRenderer();
        virtual ~OpenGLRenderer() override = default;

    private:
        SharedRef<OpenGLMainShaderProgram> m_mainShaderProgram;
    };

}// namespace Nenuphar