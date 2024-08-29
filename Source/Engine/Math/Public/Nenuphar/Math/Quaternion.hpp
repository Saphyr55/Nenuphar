#pragma once

#include "Nenuphar/Math/CommonMath.hpp"
#include "Nenuphar/Math/Matrix4.hpp"
#include "Nenuphar/Math/Vector3.hpp"

class Quaternion
{
public:
    /**
	 * Compute the euclidean norm.
	 *
	 * @brief
	 * @param vec four dimensional vector.
	 * @return
	 */
    static float Norm(const Quaternion& quaternion);

    static Quaternion Normalize(const Quaternion& quaternion);

    static Quaternion Conjugate(const Quaternion& quaternion);

    static Matrix4f ToMat4f(const Quaternion& quaternion);

    Quaternion operator*(const Quaternion& quaternion) const;
    Quaternion operator*(const Vector3f& vec) const;

public:
    float X;
    float Y;
    float Z;
    float W;
};
