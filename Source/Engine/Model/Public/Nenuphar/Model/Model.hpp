#pragma once

#include "Nenuphar/Math/Vector3.hpp"
#include "Nenuphar/Rendering/Mesh.hpp"
#include "Nenuphar/Rendering/Vertex.hpp"

namespace Nenuphar
{
    using ModelId = std::size_t;

    struct Model
    {
        std::vector<Mesh> Meshes;
    };

    const auto FloorModelFactory = []() {
        
        const std::vector<Vertex> Vertices
        {
            Vertex{Vector3f(-1.0f, 0.0f, 1.0f), Vector3f(1.0f, 1.0f, 1.0f), Vector2f(0.0f, 0.0f)},
            Vertex{Vector3f(-1.0f, 0.0f, -1.0f), Vector3f(1.0f, 1.0f, 1.0f), Vector2f(0.0f, 1.0f)},
            Vertex{Vector3f(1.0f, 0.0f, -1.0f), Vector3f(1.0f, 1.0f, 1.0f), Vector2f(1.0f, 1.0f)},
            Vertex{Vector3f(1.0f, 0.0f, 1.0f), Vector3f(1.0f, 1.0f, 1.0f), Vector2f(1.0f, 0.0f)}
        };

        // Indices for vertices order
        std::vector<VIndice> Indices =
        {
            0, 1, 2,
            0, 2, 3
        };

        return Model({Mesh(std::move(Vertices), std::move(Indices), { })});
    };

    const auto CubeModelFactory = []() {
        const std::vector<Vertex> CubeVertices{
            Vertex(Vector3f(-0.5f, -0.5f, 0.5f)),
            Vertex(Vector3f(-0.5f, -0.5f, -0.5f)),
            Vertex(Vector3f(0.5f, -0.5f, -0.5f)),
            Vertex(Vector3f(0.5f, -0.5f, 0.5f)),
            Vertex(Vector3f(-0.5f, 0.5f, 0.5f)),
            Vertex(Vector3f(-0.5f, 0.5f, -0.5f)),
            Vertex(Vector3f(0.5f, 0.5f, -0.5f)),
            Vertex(Vector3f(0.5f, 0.5f, 0.5f))
        };

        const std::vector<VIndice> CubeIndices{
                0, 1, 2,
                0, 2, 3,
                0, 4, 7,
                0, 7, 3,
                3, 7, 6,
                3, 6, 2,
                2, 6, 5,
                2, 5, 1,
                1, 5, 4,
                1, 4, 0,
                4, 5, 6,
                4, 6, 7};

        return Model({Mesh(std::move(CubeVertices), std::move(CubeIndices), {})});
    };
}