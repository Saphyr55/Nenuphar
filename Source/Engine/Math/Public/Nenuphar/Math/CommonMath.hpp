#pragma once

#include <cmath>
#include <cfloat>

#include "Nenuphar/Common/Common.hpp"

#define D_PI 3.14159265358979323846264338327950288

#define D_OPERATIONS(Type, R) \
auto operator*(const Real auto&) const \
auto operator+(const Real auto&) const; \
auto operator-(const Real auto&) const; \
auto operator*(const Type<R>&) const; \
auto operator+(const Type<R>&) const; \
auto operator-(const Type<R>&) const; \
auto operator-() const;

template<typename R>
concept Real = std::is_floating_point_v<R> || std::is_integral_v<R>;

namespace Nenuphar
{

    constexpr Float FullCircle = 2 * D_PI;
    constexpr Float PolarCap = D_PI - FLT_EPSILON;

    Double Radians(const Real auto& angle)
    {
        return angle * (D_PI / 180);
    }

    Double Signum(const Real auto& r)
    {
        return r == 0 ? 0 : std::abs(r) / r;
    }

}



