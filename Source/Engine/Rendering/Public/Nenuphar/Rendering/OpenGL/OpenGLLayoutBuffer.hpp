#pragma once


#include "Nenuphar/Rendering/Vertex.hpp"

#include <glad/glad.h>

namespace Nenuphar
{

    struct LayoutBuffer
    {
        UInt Index;
        Int Size;
        UInt Type;
        Int Stride;
        VoidPtr Offset;
        Bool Normalized;
    };


    static const std::vector<LayoutBuffer> LayoutVertex{
            {0, 3, GL_FLOAT, sizeof(VertexMinimalInfo), (VoidPtr) (0 * sizeof(Float))},
            {1, 3, GL_FLOAT, sizeof(VertexMinimalInfo), (VoidPtr) (3 * sizeof(Float))},
            {2, 2, GL_FLOAT, sizeof(VertexMinimalInfo), (VoidPtr) (6 * sizeof(Float))},
    };

    const std::vector<VertexMinimalInfo> CubeVertices{
            {{-0.5f, -0.5f, -0.5f}, {0.0f, 0.0f}},
            {{0.5f, -0.5f, -0.5f}, {1.0f, 0.0f}},
            {{0.5f, 0.5f, -0.5f}, {1.0f, 1.0f}},
            {{0.5f, 0.5f, -0.5f}, {1.0f, 1.0f}},
            {{-0.5f, 0.5f, -0.5f}, {0.0f, 1.0f}},
            {{-0.5f, -0.5f, -0.5f}, {0.0f, 0.0f}},
            {{-0.5f, -0.5f, 0.5f}, {0.0f, 0.0f}},
            {{0.5f, -0.5f, 0.5f}, {1.0f, 0.0f}},
            {{0.5f, 0.5f, 0.5f}, {1.0f, 1.0f}},
            {{0.5f, 0.5f, 0.5f}, {1.0f, 1.0f}},
            {{-0.5f, 0.5f, 0.5f}, {0.0f, 1.0f}},
            {{-0.5f, -0.5f, 0.5f}, {0.0f, 0.0f}},
            {{-0.5f, 0.5f, 0.5f}, {1.0f, 0.0f}},
            {{-0.5f, 0.5f, -0.5f}, {1.0f, 1.0f}},
            {{-0.5f, -0.5f, -0.5f}, {0.0f, 1.0f}},
            {{-0.5f, -0.5f, -0.5f}, {0.0f, 1.0f}},
            {{-0.5f, -0.5f, 0.5f}, {0.0f, 0.0f}},
            {{-0.5f, 0.5f, 0.5f}, {1.0f, 0.0f}},
            {{0.5f, 0.5f, 0.5f}, {1.0f, 0.0f}},
            {{0.5f, 0.5f, -0.5f}, {1.0f, 1.0f}},
            {{0.5f, -0.5f, -0.5f}, {0.0f, 1.0f}},
            {{0.5f, -0.5f, -0.5f}, {0.0f, 1.0f}},
            {{0.5f, -0.5f, 0.5f}, {0.0f, 0.0f}},
            {{0.5f, 0.5f, 0.5f}, {1.0f, 0.0f}},
            {{-0.5f, -0.5f, -0.5f}, {0.0f, 1.0f}},
            {{0.5f, -0.5f, -0.5f}, {1.0f, 1.0f}},
            {{0.5f, -0.5f, 0.5f}, {1.0f, 0.0f}},
            {{0.5f, -0.5f, 0.5f}, {1.0f, 0.0f}},
            {{-0.5f, -0.5f, 0.5f}, {0.0f, 0.0f}},
            {{-0.5f, -0.5f, -0.5f}, {0.0f, 1.0f}},
            {{-0.5f, 0.5f, -0.5f}, {0.0f, 1.0f}},
            {{0.5f, 0.5f, -0.5f}, {1.0f, 1.0f}},
            {{0.5f, 0.5f, 0.5f}, {1.0f, 0.0f}},
            {{0.5f, 0.5f, 0.5f}, {1.0f, 0.0f}},
            {{-0.5f, 0.5f, 0.5f}, {0.0f, 0.0f}},
            {{-0.5f, 0.5f, -0.5f}, {0.0f, 1.0f}},
    };
}
