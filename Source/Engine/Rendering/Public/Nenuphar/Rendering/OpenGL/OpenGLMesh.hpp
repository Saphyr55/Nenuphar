#pragma once

#include <vector>

#include "Nenuphar/Rendering/OpenGL/Vertex.hpp"
#include "Nenuphar/Rendering/OpenGL/OpenGLTexture.hpp"
#include "Nenuphar/Rendering/OpenGL/OpenGLBuffer.hpp"
#include "Nenuphar/Rendering/OpenGL/OpenGLShader.hpp"
#include "Nenuphar/Rendering/OpenGL/OpenGLVertexArray.hpp"

namespace Nenuphar::OpenGL
{

    template<typename V = Vertex>
    constexpr auto DefaultVertices =
            []() -> std::vector<V>
            {
                return std::vector<V>
                {
                    V { {  1.0f,  1.0f, 0.0f } },
                    V { {  1.0f, -1.0f, 0.0f } },
                    V { { -1.0f, -1.0f, 0.0f } },
                    V { { -1.0f,  1.0f, 0.0f } },
                };
            };

    constexpr auto DefaultIndices =
            []() -> std::vector<UInt32>
            {
                return std::vector<UInt32>
                        { 0, 2, 1,
                          3, 2, 0, };
            };

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
        auto CreateMesh(
                const std::vector<V>& vertices,
                const std::vector<UInt32>& indices,
                const std::vector<OpenGLTexture2D>& textures = { }
        ) -> OpenGLMesh<V>;

        template<typename V>
        auto Draw(const OpenGLShader& shader, const OpenGLMesh<V>& mesh) -> void;

    };

    template<typename V>
    auto OpenGLMeshSystem::CreateMesh(
            const std::vector<V>& vertices,
            const std::vector<UInt32>& indices,
            const std::vector<OpenGLTexture2D>& textures
    ) -> OpenGLMesh<V>
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
    auto OpenGLMeshSystem::Draw(const OpenGLShader& shader, const OpenGLMesh<V>& mesh) -> void
    {
        shader.Use();
        mesh.VAO.Bind();
        glDrawElements(GL_TRIANGLES, (Int) mesh.Indices.size(), GL_UNSIGNED_INT, nullptr);
        mesh.VAO.Unbind();
    }

}
