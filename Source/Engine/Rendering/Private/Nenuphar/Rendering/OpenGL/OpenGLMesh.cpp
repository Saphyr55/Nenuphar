#include "Nenuphar/Rendering/OpenGL/OpenGLMesh.hpp"
#include "Nenuphar/Common/Debug/Debug.hpp"
#include "Nenuphar/Common/Instanciate.hpp"
#include "Nenuphar/Common/Type/Type.hpp"
#include "Nenuphar/Rendering/Mesh.hpp"
#include "Nenuphar/Rendering/OpenGL/OpenGLBuffer.hpp"
#include "Nenuphar/Rendering/OpenGL/OpenGLDebugger.hpp"
#include "Nenuphar/Rendering/OpenGL/OpenGLLayoutBuffer.hpp"
#include "Nenuphar/Rendering/OpenGL/OpenGLTexture.hpp"
#include "Nenuphar/Rendering/OpenGL/OpenGLVertexArray.hpp"
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

        OpenGLMeshStorage::GetGlobalStorage().insert({
                meshId,
                OpenGLMesh(meshId, std::move(vao), count)
        });
    }

    void OpenGLDrawMesh(const MeshId& id)
    {
        CHECK(OpenGLMeshStorage::GetGlobalStorage().contains(id))
        CHECK(MeshStorage::GetGlobalStorage().contains(id))

        auto& openGLMesh = OpenGLMeshStorage::GetGlobalStorage().at(id);
        auto& mesh = MeshStorage::GetGlobalStorage().at(id);

        for (const auto& texture: mesh.Textures)
        {
            if (OpenGLTextureStorage::GetGlobalStorageTexture2D()
                        .contains(texture))
            {
                SharedRef<OpenGLTexture2D> openGLTexture =
                        OpenGLTextureStorage::GetGlobalStorageTexture2D()
                                .at(texture);
                ActiveTexture(openGLTexture->GetUnit());
                openGLTexture->Bind();
            }
        }
        ActiveTexture(0);

        openGLMesh.VAO->Bind();

        NPOGL_CHECK_CALL(glDrawElements(
                GL_TRIANGLES, openGLMesh.Count, GL_UNSIGNED_INT, 0));

        openGLMesh.VAO->Unbind();
    }
}