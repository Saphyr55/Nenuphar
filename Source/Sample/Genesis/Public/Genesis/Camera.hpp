#pragma once

#include "Nenuphar/ApplicationCore/WindowDefinition.hpp"
#include "Nenuphar/InputSystem/Event.hpp"
#include "Nenuphar/Math/Camera.hpp"


namespace Np = Nenuphar;


struct Velocity
{
    Float Factor;
};


void InitCamera(const WindowSignals& signals,
                Np::OrbitCamera& camera,
                const Velocity& velocity);


void ResetCameraTarget(const Np::KeyEvent& evt,
                       Np::OrbitCamera& camera);


void OnMoveCameraXY(const Np::MouseMoveEvent& evt,
                    Np::OrbitCamera& camera,
                    const Velocity& velocity);


void OnRotateCamera(const Np::MouseMoveEvent& evt,
                    Np::OrbitCamera& camera,
                    const Velocity& velocity);


void OnMoveCameraZOnScroll(const Np::MouseWheelEvent& evt,
                           Np::OrbitCamera& camera,
                           const Velocity& velocity);
