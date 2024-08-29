#pragma once

#include "Nenuphar/ApplicationCore/WindowSignals.hpp"
#include "Nenuphar/InputSystem/Event.hpp"
#include "Nenuphar/Math/Camera.hpp"

namespace Np = Nenuphar;

struct Velocity
{
    Float Factor;
};

constexpr auto DefaultOrbitCameraFactory = [] {
    Float theta = Radians(45.0f);
    Float phi = Radians(45.0f);
    Float radius = 3.0f;
    Vector3f target(0.0, 0.0, 0.0);
    Vector3f up(0.0f, 1.0f, 0.0f);
    return OrbitCamera(theta, phi, radius, target, up);
};

void InitCamera(const WindowSignals& signals,
                Np::OrbitCamera& camera,
                const Velocity& velocity);

void ResetCameraTarget(const Np::KeyEvent& evt, Np::OrbitCamera& camera);

void OnMoveCameraXY(const Np::MouseMoveEvent& evt,
                    Np::OrbitCamera& camera,
                    const Velocity& velocity);

void OnRotateCamera(const Np::MouseMoveEvent& evt,
                    Np::OrbitCamera& camera,
                    const Velocity& velocity);

void OnMoveCameraZOnScroll(const Np::MouseWheelEvent& evt,
                           Np::OrbitCamera& camera,
                           const Velocity& velocity);
