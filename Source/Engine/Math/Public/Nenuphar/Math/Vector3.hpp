#pragma once

#include "Nenuphar/Common/Common.hpp"
#include "Nenuphar/Math/CommonMath.hpp"
#include "Nenuphar/Math/Vector2.hpp"

template<Real R>
struct Vector3
{
    using Vec = Vector3;

    R x = 0;
    R y = 0;
    R z = 0;

    constexpr Vector3() = default;
    constexpr Vector3(R x, R y, R z);
    constexpr Vector3(Vector2<R> vec, R z);
    constexpr explicit Vector3(R r);

    auto Dot(const Vec& vec) const;

    Vector3 operator*(const Real auto&) const;
    Vector3 operator+(const Real auto&) const;
    Vector3 operator-(const Real auto&) const;
    Vector3 operator*(const Vec& vec) const;
    Vector3 operator+(const Vec& vec) const;
    Vector3 operator-(const Vec& vec) const;
    Vector3 operator-() const;

    constexpr bool operator==(const Vector3& other) const
    {
        return x == other.x && y == other.y && z == other.z;
    }

    constexpr bool operator!=(const Vec& other) const
    {
        return !(*this == other);
    }

    static Float Length(const Vector3<R>& vec);
    static Vector3 Normalize(const Vector3<R>& vec);
    static Vector3 Cross(const Vector3<R>& v1, const Vector3<R>& v2);
    static auto Dot(const Vec& v1, const Vec& v2);
};

using Vector3f = Vector3<Float>;
using Vector3d = Vector3<Double>;
using Vector3i = Vector3<Int>;
using Vector3u = Vector3<UInt>;

#include "Nenuphar/Math/Vector3.inl"
