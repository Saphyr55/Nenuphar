#pragma once

#include "Nenuphar/Math/Vector2.hpp"
#include "Nenuphar/Math/Vector3.hpp"

namespace Nenuphar
{
    using VIndice = UInt;

    struct VertexMinimalInfo
    {
        Vector3f Pos;
        Vector2f UV;
    };

    struct Vertex
    {
        Vector3f Pos;
        Vector3f Normal;
        Vector2f UV;

        bool operator==(const Vertex& other) const
        {
            return Pos == other.Pos && Normal == other.Normal && UV == other.UV;
        }

        bool operator!=(const Vertex& other) const
        {
            return !(*this == other);
        }

    };

}// namespace Nenuphar

