#pragma once

#include "Nenuphar/Common/Common.hpp"
#include "Nenuphar/Math/CommonMath.hpp"

using namespace Nenuphar;

template<Real R>
struct Vector2 final
{

    using Vec = Vector2;

	R x = 0;
	R y = 0;

	auto Dot(const Vec& vec) const -> auto;

	Vec operator*(const Real auto&) const;
	Vec operator+(const Real auto&) const;
	Vec operator-(const Real auto&) const;
	Vec operator*(const Vec&) const;
	Vec operator+(const Vec&) const;
	Vec operator-(const Vec&) const;
	Vec operator-() const;

};

using Vector2f = Vector2<Float>;
using Vector2d = Vector2<Double>;
using Vector2i = Vector2<Int>;
using Vector2u = Vector2<UInt>;

#include "Vector2.inl"

