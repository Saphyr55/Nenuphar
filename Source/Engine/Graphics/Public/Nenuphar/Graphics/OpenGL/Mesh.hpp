#pragma once

#include <vector>

#include "Core/Decorator.hpp"
#include "Graphics/OpenGL/Vertex.hpp"
#include "Graphics/OpenGL/Texture.hpp"
#include "Graphics/OpenGL/Buffer.hpp"
#include "Graphics/OpenGL/VertexArray.hpp"
#include "Graphics/OpenGL/Shader.hpp"

namespace Phaos::OpenGL
{

    template<typename V>
    constexpr Olambda DefaultVertices =
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

    constexpr Olambda DefaultIndices =
            []() -> std::vector<u32>
            {
                return std::vector<u32>
                        { 0, 2, 1,
                          3, 2, 0,
                        };
            };

    using MeshId = u32;

    template<typename V = Vertex>
    struct Mesh
    {
        MeshId Id{};
        std::vector<V> Vertices;
        std::vector<u32> Indices;
        std::vector<Texture2d> Textures;
        VertexArray VAO;
        Buffer<V, BufferTarget::ArrayBuffer> VBO;
        ElementBuffer EBO;
    };

    struct MeshSystem
    {

        template<typename V>
        auto CreateMesh(
                const std::vector<V>& vertices,
                const std::vector<u32>& indices,
                const std::vector<Texture2d>& textures = { }
        ) -> Mesh<V>;

        template<typename V>
        auto Draw(const Shader& shader, const Mesh<V>& mesh) -> void;

    };

    template<typename V>
    auto MeshSystem::CreateMesh(
            const std::vector<V>& vertices,
            const std::vector<u32>& indices,
            const std::vector<Texture2d>& textures
    ) -> Mesh<V>
    {

        static MeshId id;

        return Mesh<V>
            {
                id++,
                vertices,
                indices,
                textures,
                VertexArray(),
                Buffer<V, BufferTarget::ArrayBuffer>(vertices),
                ElementBuffer(indices)
            };
    }

    template<typename V>
    auto MeshSystem::Draw(const Shader& shader, const Mesh<V>& mesh) -> void
    {
        shader.Use();
        mesh.VAO.Bind();
        glDrawElements(GL_TRIANGLES, (s32) mesh.Indices.size(), GL_UNSIGNED_INT, 0);
        mesh.VAO.Unbind();
    }

}
