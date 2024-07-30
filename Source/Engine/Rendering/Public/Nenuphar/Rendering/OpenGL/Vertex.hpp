#pragma once

#include "Nenuphar/Math/Vector3.hpp"
#include "Nenuphar/Math/Vector2.hpp"

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

    struct Vertex final
    {
        Vector3f Pos;
        Vector2f UV;
    };

    static const std::vector<LayoutBuffer> LayoutVertex
    {
        { 0, 3, GL_FLOAT, sizeof(Vertex), nullptr                       },
        { 1, 2, GL_FLOAT, sizeof(Vertex), (VoidPtr) (3 * sizeof(Float)) },
    };

    struct ShapeVertex final
    {
        Vector3f Location;
        Vector2f UV;
    };

    static const std::vector<LayoutBuffer> LayoutShapeVertex =
    {
        { 0, 3, GL_FLOAT, sizeof(ShapeVertex), nullptr                       },
        { 1, 2, GL_FLOAT, sizeof(ShapeVertex), (VoidPtr) (3 * sizeof(Float)) },
    };

    const std::vector<Vertex> CubeVertices =
    {
            {{-0.5f, -0.5f, -0.5f},  {0.0f, 0.0f}},
            {{ 0.5f, -0.5f, -0.5f},  {1.0f, 0.0f}},
            {{ 0.5f,  0.5f, -0.5f},  {1.0f, 1.0f}},
            {{ 0.5f,  0.5f, -0.5f},  {1.0f, 1.0f}},
            {{-0.5f,  0.5f, -0.5f},  {0.0f, 1.0f}},
            {{-0.5f, -0.5f, -0.5f},  {0.0f, 0.0f}},
            {{-0.5f, -0.5f,  0.5f},  {0.0f, 0.0f}},
            {{ 0.5f, -0.5f,  0.5f},  {1.0f, 0.0f}},
            {{ 0.5f,  0.5f,  0.5f},  {1.0f, 1.0f}},
            {{ 0.5f,  0.5f,  0.5f},  {1.0f, 1.0f}},
            {{-0.5f,  0.5f,  0.5f},  {0.0f, 1.0f}},
            {{-0.5f, -0.5f,  0.5f},  {0.0f, 0.0f}},
            {{-0.5f,  0.5f,  0.5f},  {1.0f, 0.0f}},
            {{-0.5f,  0.5f, -0.5f},  {1.0f, 1.0f}},
            {{-0.5f, -0.5f, -0.5f},  {0.0f, 1.0f}},
            {{-0.5f, -0.5f, -0.5f},  {0.0f, 1.0f}},
            {{-0.5f, -0.5f,  0.5f},  {0.0f, 0.0f}},
            {{-0.5f,  0.5f,  0.5f},  {1.0f, 0.0f}},
            {{ 0.5f,  0.5f,  0.5f},  {1.0f, 0.0f}},
            {{ 0.5f,  0.5f, -0.5f},  {1.0f, 1.0f}},
            {{ 0.5f, -0.5f, -0.5f},  {0.0f, 1.0f}},
            {{ 0.5f, -0.5f, -0.5f},  {0.0f, 1.0f}},
            {{ 0.5f, -0.5f,  0.5f},  {0.0f, 0.0f}},
            {{ 0.5f,  0.5f,  0.5f},  {1.0f, 0.0f}},
            {{-0.5f, -0.5f, -0.5f},  {0.0f, 1.0f}},
            {{ 0.5f, -0.5f, -0.5f},  {1.0f, 1.0f}},
            {{ 0.5f, -0.5f,  0.5f},  {1.0f, 0.0f}},
            {{ 0.5f, -0.5f,  0.5f},  {1.0f, 0.0f}},
            {{-0.5f, -0.5f,  0.5f},  {0.0f, 0.0f}},
            {{-0.5f, -0.5f, -0.5f},  {0.0f, 1.0f}},
            {{-0.5f,  0.5f, -0.5f},  {0.0f, 1.0f}},
            {{ 0.5f,  0.5f, -0.5f},  {1.0f, 1.0f}},
            {{ 0.5f,  0.5f,  0.5f},  {1.0f, 0.0f}},
            {{ 0.5f,  0.5f,  0.5f},  {1.0f, 0.0f}},
            {{-0.5f,  0.5f,  0.5f},  {0.0f, 0.0f}},
            {{-0.5f,  0.5f, -0.5f},  {0.0f, 1.0f}},
    };


}
