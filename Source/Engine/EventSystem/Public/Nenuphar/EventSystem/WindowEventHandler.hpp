#pragma once

#include "Nenuphar/ApplicationCore/WindowInterface.hpp"
#include "Nenuphar/InputSystem/Event.hpp"
#include "Nenuphar/EventSystem/EventBus.hpp"
#include "Nenuphar/EventSystem/Event.hpp"

namespace Nenuphar
{

    class WindowEventHandler
    {
    public:
        explicit WindowEventHandler(const WindowID ID_) : ID(ID_) { }

        NPSignal(OnClose,           CloseEvent,   "Nenuphar.WindowEvent.Window.On-Close.ID-" + ID)
        NPSignal(OnResize,          ResizeEvent,      "Nenuphar.WindowEvent.Mouse.On-Resize.ID-" + ID)
        NPSignal(OnMouseWheel,      MouseWheelEvent,    "Nenuphar.WindowEvent.Mouse.Mouse-Wheel.ID-" + ID)
        NPSignal(OnButtonPressed,   MouseButtonEvent,   "Nenuphar.WindowEvent.Mouse.Button-Pressed.ID-" + ID)
        NPSignal(OnButtonRelease,   MouseButtonEvent,   "Nenuphar.WindowEvent.Mouse.Button-Release.ID-" + ID)
        NPSignal(OnMouseMove,       MouseMoveEvent,     "Nenuphar.WindowEvent.Mouse-Motion.ID-" + ID)
        NPSignal(OnKeyDown,         KeyEvent,           "Nenuphar.WindowEvent.Key.Key-Down.ID-" + ID)
        NPSignal(OnKeyRelease,      KeyEvent,           "Nenuphar.WindowEvent.Key.Key-Release.ID-" + ID)
        NPSignal(OnKeyPressed,      KeyEvent,           "Nenuphar.WindowEvent.Key.Key-Pressed.ID-" + ID)

    private:
        WindowID ID;
    };

}
