#pragma once

#include "Nenuphar/Math/Matrix4.hpp"
#include "Nenuphar/Math/Vector3.hpp"

namespace gn
{

    struct Transform
    {
        Vector3f Translation;
        Vector3f Rotation;
        Vector3f Scale;

        static Matrix4f Tranformation(const Transform& transform);
    };

}