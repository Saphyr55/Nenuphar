#include "Nenuphar/Rendering/OpenGL/OpenGLRenderer.hpp"
#include "Nenuphar/Common/Instanciate.hpp"
#include "Nenuphar/Common/Type/Type.hpp"
#include "Nenuphar/Core/Debug.hpp"
#include "Nenuphar/Rendering/ImageAsset.hpp"
#include "Nenuphar/Rendering/Mesh.hpp"
#include "Nenuphar/Rendering/OpenGL/OpenGLMainShader.hpp"
#include "Nenuphar/Rendering/OpenGL/OpenGLMesh.hpp"
#include "Nenuphar/Rendering/OpenGL/OpenGLTexture.hpp"
#include "Nenuphar/Rendering/OpenGL/OpenGLVertexArray.hpp"
#include "Nenuphar/Rendering/RenderObject.hpp"
#include "Nenuphar/Rendering/Shader.hpp"
#include "Nenuphar/Rendering/Texture.hpp"
#include <memory>

namespace Nenuphar
{
    // TODO: Use a sparse set and the pagination technique to have better perfomance.
    static std::vector<std::vector<MeshId>> ModelStorage;

    OpenGLRenderer::OpenGLRenderer()
    {
        m_mainShaderProgram = MakeSharedRef<OpenGLMainShaderProgram>();
        m_mainShaderProgram->Initialize();
    }

    SharedRef<MainShaderProgram> OpenGLRenderer::GetMainShaderProgram()
    {
        return m_mainShaderProgram;
    }
    
    RenderObject OpenGLRenderer::SubmitRenderData(
            const std::vector<Vertex>& vertices,
            const std::vector<VIndice>& indices) const
    {
        Int count = indices.size();

        auto vbo = OpenGLImmutableBuffer::Create(vertices);
        auto ebo = OpenGLImmutableBuffer::Create(indices);
        auto vao = OpenGLVertexArray::Create(ebo->GetHandle(), vbo->GetHandle());

        vbo->Destroy();
        ebo->Destroy();

        return RenderObject(0, vao);
    }

    void OpenGLRenderer::Render(RenderObject& object) const
    {
        auto vao = std::reinterpret_pointer_cast<OpenGLVertexArray>(object.InternalState);
        vao->Bind();
        NP_GL_CHECK_CALL(glDrawElements(GL_TRIANGLES, glMesh.Count, GL_UNSIGNED_INT, 0));
    }


}// namespace Nenuphar
