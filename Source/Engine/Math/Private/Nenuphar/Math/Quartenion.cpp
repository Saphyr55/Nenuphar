#include "Nenuphar/Math/Matrix4.hpp"
#include "Nenuphar/Math/Quaternion.hpp"
#include "Nenuphar/Math/Vector3.hpp"

static Matrix4f ToMat4f(const Quaternion& q)
{
    Matrix4f Result = Matrix4f::Identity();
    Float qxx(q.X * q.X);
    Float qyy(q.Y * q.Y);
    Float qzz(q.Z * q.Z);
    Float qxz(q.X * q.Z);
    Float qxy(q.X * q.Y);
    Float qyz(q.Y * q.Z);
    Float qwx(q.W * q.X);
    Float qwy(q.W * q.Y);
    Float qwz(q.W * q.Z);

    Result[0][0] = Float(1) - Float(2) * (qyy + qzz);
    Result[0][1] = Float(2) * (qxy + qwz);
    Result[0][2] = Float(2) * (qxz - qwy);

    Result[1][0] = Float(2) * (qxy - qwz);
    Result[1][1] = Float(1) - Float(2) * (qxx + qzz);
    Result[1][2] = Float(2) * (qyz + qwx);

    Result[2][0] = Float(2) * (qxz + qwy);
    Result[2][1] = Float(2) * (qyz - qwx);
    Result[2][2] = Float(1) - Float(2) * (qxx + qyy);
    
    return Result;
}

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
