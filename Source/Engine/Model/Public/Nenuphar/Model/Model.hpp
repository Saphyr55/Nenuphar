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

    const Model CubeModel = []() {
        
        const std::vector<Vertex> CubeVertices{
                Vertex{Vector3f(-0.05f, -0.05f, 0.05f)},
                Vertex{Vector3f(-0.05f, -0.05f, -0.05f)},
                Vertex{Vector3f(0.05f, -0.05f, -0.05f)},
                Vertex{Vector3f(0.05f, -0.05f, 0.05f)},
                Vertex{Vector3f(-0.05f, 0.05f, 0.05f)},
                Vertex{Vector3f(-0.05f, 0.05f, -0.05f)},
                Vertex{Vector3f(0.05f, 0.05f, -0.05f)},
                Vertex{Vector3f(0.05f, 0.05f, 0.05f)}};

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
        
        return Model({Mesh(CubeVertices, CubeIndices, { })});
    }();
}