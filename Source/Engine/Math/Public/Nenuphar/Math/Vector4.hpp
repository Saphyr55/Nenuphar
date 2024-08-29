#pragma once

#include "Nenuphar/Math/Vector3.hpp"

template<Real R>
struct Vector4
{
    R x = 0;
    R y = 0;
    R z = 0;
    R w = 0;

    Vector4() = default;
    explicit Vector4(R r);
    explicit Vector4(Vector3<R> vec, R w = 1);
    Vector4(R x, R y, R z, R w);

    auto Dot(const Vector4& vec) const;
    R& operator[](std::size_t i);
    const R& operator[](std::size_t i) const;

    Vector4 operator*(const Real auto&) const;
    Vector4 operator+(const Real auto&) const;
    Vector4 operator-(const Real auto&) const;
    Vector4 operator/(const Real auto&) const;
    Vector4 operator*(const Vector4& vec) const;
    Vector4 operator/(const Vector4& vec) const;
    Vector4 operator+(const Vector4& vec) const;
    Vector4 operator-(const Vector4& vec) const;
    Vector4 operator-() const;

    /**
	 * Compute the euclidean norm.
	 *
	 * \brief
	 * \param vec four dimensional vector.
	 * \return
	 */
    static Float Norm(Vector4 vec);
    static Vector4<Float> Normalize(Vector4 vec);
};

using Vector4f = Vector4<Float>;
using Vector4d = Vector4<Double>;
using Vector4i = Vector4<Int>;
using Vector4u = Vector4<UInt>;

#include "Nenuphar/Math/Vector4.inl"
