#pragma once

#include <cfloat>
#include <cmath>

#define NOPERATIONS(Type, R)                                                      \
    auto operator*(const Real auto&) const auto operator+(const Real auto&) const; \
    auto operator-(const Real auto&) const;                                        \
    auto operator*(const Type<R>&) const;                                          \
    auto operator+(const Type<R>&) const;                                          \
    auto operator-(const Type<R>&) const;                                          \
    auto operator-() const;

template<typename R>
concept Real = std::is_floating_point_v<R> || std::is_integral_v<R>;

namespace Nenuphar
{
    constexpr float Pi = float(3.14159265358979323846264338327950288);
    constexpr float FullCircle = 2 * Pi;
    constexpr float PolarCap = Pi - FLT_EPSILON;

    constexpr inline auto Radians(const Real auto& angle)
    {
        return angle * (Pi / 180);
    }

    constexpr inline auto Signum(const Real auto& r)
    {
        return r == 0 ? 0 : std::abs(r) / r;
    }

}// namespace Nenuphar
