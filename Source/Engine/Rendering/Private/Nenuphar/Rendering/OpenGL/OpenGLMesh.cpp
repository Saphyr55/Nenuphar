#include "Nenuphar/Rendering/OpenGL/OpenGLMesh.hpp"
#include "Nenuphar/Common/Instanciate.hpp"
#include "Nenuphar/Common/Type/Type.hpp"
#include "Nenuphar/Core/Debug.hpp"
#include "Nenuphar/Rendering/Mesh.hpp"
#include "Nenuphar/Rendering/OpenGL/OpenGLBuffer.hpp"
#include "Nenuphar/Rendering/OpenGL/OpenGLDebugger.hpp"
#include "Nenuphar/Rendering/OpenGL/OpenGLLayoutBuffer.hpp"
#include "Nenuphar/Rendering/OpenGL/OpenGLShader.hpp"
#include "Nenuphar/Rendering/OpenGL/OpenGLTexture.hpp"
#include "Nenuphar/Rendering/OpenGL/OpenGLVertexArray.hpp"
#include "Nenuphar/Rendering/OpenGL/Uniform.hpp"
#include "Nenuphar/Rendering/Texture.hpp"
#include "Nenuphar/Rendering/Vertex.hpp"


#include <cstdlib>


namespace Nenuphar
{
    OpenGLMeshStorage OpenGLMeshStorage::s_mainStorage;

    OpenGLMeshStorage::TStorage& OpenGLMeshStorage::GetGlobalStorage()
    {
        return OpenGLMeshStorage::s_mainStorage.m_storage;
    }

    void OpenGLPersistMesh(const MeshId& meshId)
    {
        Mesh& mesh = MeshStorage::GetGlobalStorage()[meshId];
        Int count = mesh.Indices.size();

        auto vao = MakeUnique<OpenGLVertexArray>();
        OpenGLArrayBuffer<> vbo(mesh.Vertices);
        OpenGLElementBuffer ebo(mesh.Indices);

        LinkBuffer(vbo, LayoutVertex);

        vao->Unbind();
        vbo.Unbind();
        ebo.Unbind();

        OpenGLMeshStorage::GetGlobalStorage().insert({meshId,
                                                      OpenGLMesh(meshId, std::move(vao), count)});
    }

    void OpenGLDrawMesh(UniformRegistry& registry, const MeshId& id)
    {

        NCHECK(OpenGLMeshStorage::GetGlobalStorage().contains(id))
        NCHECK(MeshStorage::GetGlobalStorage().contains(id))

        auto& glMesh = OpenGLMeshStorage::GetGlobalStorage().at(id);
        auto& mesh = MeshStorage::GetGlobalStorage().at(id);

        registry.Get<Bool>("UIsTextured").UpdateValue(true);

        for (UInt32 i = 0; i < mesh.Textures.size(); i++)
        {
            Texture& texture = mesh.Textures.at(i); 
            if (OpenGLTextureStorage::GetGlobalStorageTexture2D()
                        .contains(texture))
            {
                
                SharedRef<OpenGLTexture2D> openGLTexture =
                        OpenGLTextureStorage::GetGlobalStorageTexture2D()
                                .at(texture);

                ActiveTexture(i);
                registry.Get<Int>("UTex").UpdateValue((Int) i);
                openGLTexture->Bind();
            }
        }

        glMesh.VAO->Bind();
        NP_GL_CHECK_CALL(glDrawElements(GL_TRIANGLES, glMesh.Count, GL_UNSIGNED_INT, 0));
        glMesh.VAO->Unbind();

        ActiveTexture(0);
    }
}// namespace Nenuphar