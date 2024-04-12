#include "Nenuphar/Math/Camera.hpp"

namespace Nenuphar
{
    Vector3f Camera::Target() const
    {
        return Pos + Front;
    };

    Vector3f Camera::Right() const
    {
        return Vector3f::Normalize(Vector3f::Cross(Target(), Up));
    }

    Vector3f OrbitCamera::Position() const
    {
        return Target + Cartesian();
    }

    Vector3f OrbitCamera::Cartesian() const
    {
        float x = Radius * std::sin(Phi) * std::sin(Theta);
        float y = Radius * std::cos(Phi);
        float z = Radius * std::sin(Phi) * std::cos(Theta);
        return { x, y, z };
    }

}