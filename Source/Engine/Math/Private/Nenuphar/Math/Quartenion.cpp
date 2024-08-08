#include "Nenuphar/Math/Quaternion.hpp"
#include "Nenuphar/Math/Vector3.hpp"

float Quaternion::Norm(const Quaternion& q)
{
    return std::sqrt(q.X * q.X + q.Y * q.Y + q.Z * q.Z + q.W * q.W);
}

Quaternion Quaternion::Normalize(const Quaternion& quaternion)
{
    float quaternionNorm = Norm(quaternion);
    return Quaternion(
            quaternion.X / quaternionNorm,
            quaternion.Y / quaternionNorm,
            quaternion.Z / quaternionNorm,
            quaternion.W / quaternionNorm
    );
}

Quaternion Quaternion::Conjugate(const Quaternion& quaternion)
{
    return Quaternion(
            -quaternion.X,
            -quaternion.Y,
            -quaternion.Z,
             quaternion.W
    );
}

Quaternion Quaternion::operator*(const Quaternion& q) const
{
    float x = X * q.W + W * q.X + Y * q.Z - Z * q.Y;
    float y = Y * q.W + W * q.Y + Z * q.X - X * q.Z;
    float z = Z * q.W + W * q.Z + X * q.Y - Y * q.X;
    float w = W * q.W - X * q.X - Y * q.Y - Z * q.Z;

    return Quaternion(x, y, z, w);
}

Quaternion Quaternion::operator*(const Vector3f& vec) const
{
    float x =  W * vec.x + Y * vec.z - Z * vec.y;
    float y =  W * vec.y + Z * vec.x - X * vec.z;
    float z =  W * vec.z + X * vec.y - Y * vec.x;
    float w = -X * vec.x - Y * vec.y - Z * vec.z;

    return Quaternion(x, y, z, w);
}
