#include "Nenuphar/Rendering/OpenGL/OpenGLMesh.hpp"
#include "Nenuphar/Rendering/OpenGL/OpenGLBuffer.hpp"
#include "Nenuphar/Rendering/OpenGL/OpenGLDebugger.hpp"
#include "Nenuphar/Rendering/OpenGL/OpenGLLayoutBuffer.hpp"
#include "Nenuphar/Rendering/OpenGL/OpenGLVertexArray.hpp"
#include "Nenuphar/Rendering/Vertex.hpp"

namespace Nenuphar
{

    MeshId OpenGLPersistMesh(const Mesh& mesh)
    {
        MeshId id = Storage.size();
        OpenGLMesh glMesh;
        glMesh.mesh = mesh;
        auto vbo = OpenGLArrayBuffer<Vertex>(glMesh.mesh.Vertices);
        auto ebo = OpenGLElementBuffer(glMesh.mesh.Indices);
        auto count = glMesh.mesh.Indices.size();
        glMesh.Count = count;

        LinkBuffer(vbo, LayoutVertex);

        Storage.push_back(std::move(glMesh));

        return id;
    }

    void OpenGLDrawMesh(const MeshId& id)
    {
        auto mesh = Storage[id];
        mesh.VAO.Bind();
        NPOGL_CHECK_CALL(glDrawElements(GL_TRIANGLES, mesh.Count, GL_UNSIGNED_INT, nullptr));
        mesh.VAO.Unbind();
    }
}