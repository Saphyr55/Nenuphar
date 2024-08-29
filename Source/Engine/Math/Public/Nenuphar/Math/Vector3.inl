
#include "Nenuphar/Math/CommonMath.hpp"
#include "Nenuphar/Math/Vector3.hpp"

template<Real R>
constexpr Vector3<R>::Vector3(Vector2<R> vec, R z)
    : Vector3(vec.x, vec.y, z)
{
}

template<Real R>
constexpr Vector3<R>::Vector3(R x, R y, R z)
    : x(x), y(y), z(z)
{
}

template<Real R>
constexpr Vector3<R>::Vector3(R r)
    : Vector3(r, r, r)
{
}

template<Real R>
Float Vector3<R>::Length(const Vec& vec)
{
    return std::sqrt(vec.x * vec.x + vec.y * vec.y + vec.z * vec.z);
}

template<Real R>
Vector3<R> Vector3<R>::Normalize(const Vec& vec)
{
    auto l = Length(vec);
    return Vec(vec.x / l, vec.y / l, vec.z / l);
}

template<Real R>
Vector3<R> Vector3<R>::Cross(const Vec& v1, const Vec& v2)
{
    return Vec((v1.y * v2.z - v1.z * v2.y) * 1, 0, 0) -
           Vec(0, (v1.x * v2.z - v1.z * v2.x) * 1, 0) -
           Vec(0, 0, (v1.x * v2.y - v1.y * v2.x) * 1);
}

template<Real R>
auto Vector3<R>::Dot(const Vec& v1, const Vec& v2)
{
    return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
}

template<Real R>
Vector3<R> Vector3<R>::operator-() const
{
    return Vec{-x, -y, -z};
}

template<Real R>
auto Vector3<R>::Dot(const Vec& vec) const
{
    return vec.x * x + vec.y * y + vec.z * z;
}

#pragma region Operations Impl

template<Real R>
Vector3<R> Vector3<R>::operator*(const Real auto& t) const
{
    return Vec{x * t, y * t, z * t};
}

template<Real R>
Vector3<R> Vector3<R>::operator+(const Real auto& t) const
{
    return Vec{x + t, y + t, z + t};
}

template<Real R>
Vector3<R> Vector3<R>::operator-(const Real auto& t) const
{
    return Vec{x - t, y - t, z - t};
}

template<Real R>
Vector3<R> Vector3<R>::operator*(const Vec& vec) const
{
    return Vec{vec.x * x, vec.y * y, vec.z * z};
}

template<Real R>
Vector3<R> Vector3<R>::operator+(const Vec& vec) const
{
    return Vec{vec.x + x, vec.y + y, vec.z + z};
}

template<Real R>
Vector3<R> Vector3<R>::operator-(const Vec& vec) const
{
    return Vec{vec.x - x, vec.y - y, vec.z - z};
}

#pragma endregion
