#pragma once

#include "Nenuphar/Math/Matrix4.hpp"
#include "Nenuphar/Math/Quaternion.hpp"
#include "Nenuphar/Math/Vector3.hpp"

struct Transform
{
    Vector3f Translation;
    Vector3f Scale;
    Quaternion Rotation;

    static Matrix4f Tranformation(const Matrix4f& mat,
                                  const Transform& transform);
    static Matrix4f Tranformation(const Transform& transform);
};
