#include "Nenuphar/Math/Vector2.hpp"

template<Real R>
auto Vector2<R>::Dot(const Vec& vec) const
{
	return vec.x * x + vec.y * y;
}

template<Real R>
Vector2<R> Vector2<R>::operator*(const Real auto& t) const
{
	return Vec
	{
		x * t,
		y * t
	};
}

template<Real R>
Vector2<R> Vector2<R>::operator+(const Real auto& t) const
{
	return Vec
	{
		x + t,
		y + t
	};
}

template<Real R>
Vector2<R> Vector2<R>::operator-() const
{
    return Vec
	{
		-x,
		-y
	};
}

template<Real R>
Vector2<R> Vector2<R>::operator-(const Real auto& t) const
{
	return Vec
	{
		x - t,
		y - t
	};
}

template<Real R>
Vector2<R> Vector2<R>::operator*(const Vec& vec) const
{
	return Vec
	{
		vec.x * x,
		vec.y * y
	};
}

template<Real R>
Vector2<R> Vector2<R>::operator+(const Vec& vec) const
{
	return Vec
	{
		vec.x + x,
		vec.y + y
	};
}

template<Real R>
Vector2<R> Vector2<R>::operator-(const Vec& vec) const
{
	return Vec
	{
		vec.x - x,
		vec.y - y
	};
}
