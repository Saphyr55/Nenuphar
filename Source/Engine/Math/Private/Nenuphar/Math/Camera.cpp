#include "Nenuphar/Math/Camera.hpp"

namespace Nenuphar
{

    OrbitCamera::OrbitCamera(Float inTheta, Float inPhi, Float inRadius, Vector3f inTarget, Vector3f inUp)
            : Theta(inTheta), Phi(inPhi), Radius(inRadius), Target(inTarget), Up(inUp)
    {

    }

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

    OrbitCamera& OrbitCamera::operator=(const OrbitCamera& camera)
    {
        Theta = camera.Theta;
        Phi = camera.Phi;
        Up = camera.Up;
        Target = camera.Target;
        Radius = camera.Radius;
        return *this;
    }

    OrbitCamera& OrbitCamera::operator=(OrbitCamera&& camera)
    {
        Theta = camera.Theta;
        Phi = camera.Phi;
        Up = camera.Up;
        Target = camera.Target;
        Radius = camera.Radius;
        return *this;
    }

}