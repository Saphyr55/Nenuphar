#include "Genesis/Camera.hpp"
#include "Nenuphar/InputSystem/InputSystem.hpp"
#include "Nenuphar/Math/Camera.hpp"


static OrbitCamera DefaultCamera((float) Radians(45.0f),
                                 (float) Radians(45.0f),
                                 3.0f,
                                 Vector3f(0.0, 0.0, 0.0),
                                 Vector3f(0.0f, 1.0f, 0.0f));


void InitCamera(const WindowSignals& signals, Np::OrbitCamera& camera, const Velocity& velocity)
{
    signals.OnKeyPressed().Connect([&](auto&, auto& evt) {
        ResetCameraTarget(evt, camera);
    });

    signals.OnMouseMove().Connect([&](auto&, auto& evt) {
        OnMoveCameraXY(evt, camera, velocity);
        OnRotateCamera(evt, camera, velocity);
    });

    signals.OnMouseWheel().Connect([&](auto&, auto& evt) {
        OnMoveCameraZOnScroll(evt, camera, velocity);
    });
}


Void ResetCameraTarget(const Np::KeyEvent& evt, Np::OrbitCamera& camera)
{
    if (evt.Key == Input::Key::R)
    {
        camera.Target = DefaultCamera.Target;
    }
}


Void OnMoveCameraXY(const Np::MouseMoveEvent& evt, Np::OrbitCamera& camera, const Velocity& velocity)
{
    if (Np::InputSystem::IsButtonDown(Input::Button::Middle))
    {
        Float dx = -evt.PosRelX * (velocity.Factor * 0.1f) * camera.Radius;
        Float dy = -evt.PosRelY * (velocity.Factor * 0.1f) * camera.Radius;
        camera = OrbitCamera::PanOrbitCamera(camera, dx, dy);
    }
}


Void OnRotateCamera(const Np::MouseMoveEvent& evt, Np::OrbitCamera& camera, const Velocity& velocity)
{
    if (Np::InputSystem::IsButtonDown(Input::Button::Left))
    {
        camera = OrbitCamera::RotateTheta(camera, evt.PosRelX * velocity.Factor);
        camera = OrbitCamera::RotatePhi(camera, -evt.PosRelY * velocity.Factor);
    }
}


Void OnMoveCameraZOnScroll(const Np::MouseWheelEvent& evt, Np::OrbitCamera& camera, const Velocity& velocity)
{
    camera.Radius -= evt.Delta * velocity.Factor;
    if (camera.Radius < 3)
    {
        camera.Radius = 3;
    }
}
