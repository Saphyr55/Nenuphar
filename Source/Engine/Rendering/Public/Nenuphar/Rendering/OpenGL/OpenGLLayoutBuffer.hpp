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
        UInt Offset;
        Bool Normalized;
    };

    static const std::vector<LayoutBuffer> GLayoutVertex{
            {0, 3, GL_FLOAT, sizeof(Vertex), (0 * sizeof(Float))},
            {1, 3, GL_FLOAT, sizeof(Vertex), (3 * sizeof(Float))},
            {2, 2, GL_FLOAT, sizeof(Vertex), (6 * sizeof(Float))},
    };

}
