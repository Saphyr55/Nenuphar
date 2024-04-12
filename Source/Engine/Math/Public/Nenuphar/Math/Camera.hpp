#pragma once

#include <algorithm>
#include "Nenuphar/Common/Common.hpp"
#include "Nenuphar/Math/Math.hpp"

namespace Nenuphar
{

    struct Camera
    {
        Vector3f Pos;
        Vector3f Front;
        Vector3f Up;

        [[nodiscard]] Vector3f Target() const;

        [[nodiscard]] Vector3f Right() const;

        Camera(Camera&&) = default;
        Camera(const Camera&) = default;
        ~Camera() = default;
    };

    struct OrbitCamera
    {
        Float Theta{};
        Float Phi{};
        Float Radius{};
        Vector3f Target;
        Vector3f Up;

        [[nodiscard]] Vector3f Position() const;

        [[nodiscard]] Vector3f Cartesian() const;

        static OrbitCamera RotateTheta(const OrbitCamera& camera, const Real auto& radians);

        static OrbitCamera PanOrbitCamera(const OrbitCamera& camera, const Real auto& dx, const Real auto& dy);

        static OrbitCamera RotatePhi(const OrbitCamera& camera, const Real auto& radians);

        OrbitCamera(Float Theta, Float Phi, Float Radius, Vector3f Target, Vector3f Up);

        OrbitCamera() = default;
        OrbitCamera(OrbitCamera&&) = default;
        OrbitCamera(const OrbitCamera&) = default;
        ~OrbitCamera() = default;
    };

    OrbitCamera OrbitCamera::RotateTheta(const OrbitCamera& camera, const Real auto& radians)
    {
        OrbitCamera newCamera(camera);
        newCamera.Theta += radians;

        // Keep azimuth angle within range <0..2PI) - it's not necessary, just to have it nicely output
        newCamera.Theta = std::fmod(newCamera.Theta, FullCircle);
        if (newCamera.Theta < 0.0f)
        {
            newCamera.Theta = FullCircle + newCamera.Theta;
        }

        return newCamera;
    }

    OrbitCamera OrbitCamera::RotatePhi(const OrbitCamera& camera, const Real auto& radians)
    {
        OrbitCamera newCamera(camera);

        newCamera.Phi += radians;
        newCamera.Phi = std::clamp(camera.Phi, FLT_EPSILON, PolarCap);

        return newCamera;
    }

    OrbitCamera OrbitCamera::PanOrbitCamera(const OrbitCamera& camera, const Real auto& dx, const Real auto& dy)
    {
        OrbitCamera newCamera(camera);

        Vector3f eye = Vector3f::Normalize(newCamera.Cartesian());
        Vector3f right = Vector3f::Cross(eye, newCamera.Up);
        Vector3f up = Vector3f::Cross(eye, right);

        newCamera.Target = newCamera.Target + (right * dx) + (up * dy);

        return newCamera;
    }

    OrbitCamera::OrbitCamera(Float inTheta, Float inPhi, Float inRadius, Vector3f inTarget, Vector3f inUp)
        : Theta(inTheta), Phi(inPhi), Radius(inRadius), Target(inTarget), Up(inUp)
    {

    }

}
