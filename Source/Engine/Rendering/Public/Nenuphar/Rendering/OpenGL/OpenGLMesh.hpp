#pragma once

#include <vector>

#include "Nenuphar/Rendering/OpenGL/Vertex.hpp"
#include "Nenuphar/Rendering/OpenGL/OpenGLTexture.hpp"
#include "Nenuphar/Rendering/OpenGL/OpenGLBuffer.hpp"
#include "Nenuphar/Rendering/OpenGL/OpenGLShader.hpp"
#include "Nenuphar/Rendering/OpenGL/OpenGLVertexArray.hpp"

namespace Nenuphar::OpenGL
{

    using MeshId = UInt32;

    template<typename V = Vertex>
    struct OpenGLMesh
    {
        MeshId Id{};
        std::vector<V> Vertices;
        std::vector<UInt32> Indices;
        std::vector<OpenGLTexture2D> Textures;
        OpenGLVertexArray VAO;
        OpenGLBuffer<V, OpenGLBufferTarget::ArrayBuffer> VBO;
        OpenGLElementBuffer EBO;
    };

    struct OpenGLMeshSystem
    {
        template<typename V>
        OpenGLMesh<V> CreateMesh(
                const std::vector<V>& vertices,
                const std::vector<UInt32>& indices,
                const std::vector<OpenGLTexture2D>& textures = { });

        template<typename V>
        Void Draw(const OpenGLShader& shader, const OpenGLMesh<V>& mesh);
    };

    template<typename V>
    OpenGLMesh<V> OpenGLMeshSystem::CreateMesh(
            const std::vector<V>& vertices,
            const std::vector<UInt32>& indices,
            const std::vector<OpenGLTexture2D>& textures)
    {
        static MeshId id;
        return OpenGLMesh<V>
        {
            id++,
            vertices,
            indices,
            textures,
            OpenGLVertexArray(),
            OpenGLBuffer<V, OpenGLBufferTarget::ArrayBuffer>(vertices),
            OpenGLElementBuffer(indices)
        };
    }

    template<typename V>
    Void OpenGLMeshSystem::Draw(const OpenGLShader& shader, const OpenGLMesh<V>& mesh)
    {
        shader.Use();
        mesh.VAO.Bind();
        glDrawElements(GL_TRIANGLES, (Int) mesh.Indices.size(), GL_UNSIGNED_INT, nullptr);
        mesh.VAO.Unbind();
    }

}
