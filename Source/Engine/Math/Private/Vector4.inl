#include "Nenuphar/Math/Vector4.hpp"

template<Real R>
Vector4<R>::Vector4(Vector3<R> vec, R w) : Vector4(vec.x, vec.y, vec.z, w) { }

template<Real R>
Vector4<R>::Vector4(R x, R y, R z, R w) : x(x), y(y), z(z), w(w) { }

template<Real R>
Vector4<R>::Vector4(R r) : Vector4(r, r, r, r) { }

template<Real R>
auto Vector4<R>::Dot(const Vector4& vec) const
{
	return vec.x * x + vec.y * y + vec.z * z + vec.w * w;
}

template<Real R>
Float Vector4<R>::Norm(Vector4 vec)
{
	return std::sqrt(vec.x * vec.x + vec.y * vec.y + vec.z * vec.z + vec.w * vec.w);
}

template<Real R>
Vector4f Vector4<R>::Normalize(Vector4 vec)
{
	Float l = Norm(vec);
	return Vector4f
	{
		vec.x / l,
		vec.y / l,
		vec.z / l,
		vec.w / l
	};
}

template<Real R>
R& Vector4<R>::operator[](const std::size_t i)
{
	switch (i)
	{
		case 0: return x;
		case 1: return y;
		case 2: return z;
		case 3: return w;
		default: throw std::exception();
	}
}

template<Real R>
Vector4<R> Vector4<R>::operator*(const Real auto& t) const
{
	return Vector4
	{
		x * t,
		y * t,
		z * t,
		w * t
	};
}

template<Real R>
Vector4<R> Vector4<R>::operator+(const Real auto& t) const
{
	return Vector4
	{
		x + t,
		y + t,
		z + t,
		w + t
	};
}

template<Real R>
Vector4<R> Vector4<R>::operator-(const Real auto& t) const
{
	return Vector4
	{
		x - t,
		y - t,
		z - t,
		w - t
	};
}

template<Real R>
Vector4<R> Vector4<R>::operator/(const Real auto& t) const
{
	return Vector4
	{
		x / t,
		y / t,
		z / t,
		w / t
	};
}

template<Real R>
Vector4<R> Vector4<R>::operator-() const
{
	return Vector4
	{
		-x,
		-y,
		-z,
		-w
	};
}

template<Real R>
Vector4<R> Vector4<R>::operator*(const Vector4& vec) const
{
	return Vector4
	{
		x * vec.x,
		y * vec.y,
		z * vec.z,
		w * vec.w
	};
}

template<Real R>
Vector4<R> Vector4<R>::operator/(const Vector4& vec) const
{
	return Vector4
	{
		x / vec.x,
		y / vec.y,
		z / vec.z,
		w / vec.w
	};
}


template<Real R>
Vector4<R> Vector4<R>::operator+(const Vector4& vec) const
{
	return Vector4
	{
		x + vec.x,
		y + vec.y,
		z + vec.z,
		w + vec.w
	};
}

template<Real R>
Vector4<R> Vector4<R>::operator-(const Vector4& vec) const
{
	return Vector4
	{
		x - vec.x,
		y - vec.y,
		z - vec.z,
		w - vec.w
	};
}

