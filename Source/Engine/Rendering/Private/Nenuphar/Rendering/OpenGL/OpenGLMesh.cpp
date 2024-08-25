#include "Nenuphar/Rendering/OpenGL/OpenGLMesh.hpp"

namespace Nenuphar
{

    MeshId OpenGLPersistMesh(const Mesh& mesh)
    {
        MeshId id = Storage.size();
        Storage[id] = OpenGLMesh<Vertex>(
                OpenGLVertexArray(),
                OpenGLBuffer<Vertex, OpenGLBufferTarget::ArrayBuffer>(mesh.Vertices),
                OpenGLElementBuffer(mesh.Indices),
                mesh.Indices.size());
        return id;
    }

    void OpenGLDrawMesh(const MeshId& id)
    {
        auto mesh = Storage[id];
        mesh.VAO.Bind();
        glDrawElements(GL_TRIANGLES, mesh.Count, GL_UNSIGNED_INT, nullptr);
        mesh.VAO.Unbind();
    }
}