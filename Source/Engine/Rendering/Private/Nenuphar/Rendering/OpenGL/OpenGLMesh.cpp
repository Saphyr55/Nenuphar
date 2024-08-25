#include "Nenuphar/Rendering/OpenGL/OpenGLMesh.hpp"
#include "Nenuphar/Common/Type/Type.hpp"
#include "Nenuphar/Rendering/OpenGL/OpenGLBuffer.hpp"
#include "Nenuphar/Rendering/OpenGL/OpenGLLayoutBuffer.hpp"
#include "Nenuphar/Rendering/OpenGL/OpenGLVertexArray.hpp"

namespace Nenuphar
{

    MeshId OpenGLPersistMesh(const Mesh& mesh)
    {
        MeshId id = Storage.size();

        auto vao = OpenGLVertexArray();
        auto vbo = OpenGLArrayBuffer<Vertex>(mesh.Vertices);
        auto ebo = OpenGLElementBuffer(mesh.Indices);
        auto count = mesh.Indices.size();
        
        LinkBuffer(vbo, LayoutVertex);

        auto glMesh = OpenGLMesh<Vertex>(std::move(vao), std::move(count));

        Storage.push_back(std::move(glMesh));
        
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