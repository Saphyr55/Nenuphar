#pragma once

#include "Nenuphar/InputSystem/Event.hpp"
#include "Nenuphar/EventSystem/EventBus.hpp"
#include "Nenuphar/EventSystem/Event.hpp"

namespace Nenuphar
{

    class WindowEventHandler
    {
    public:
        NPSignal(OnResize,          OnResizeEvent,      "Nenuphar.Event.Mouse.On-Resize")
        NPSignal(OnMouseWheel,      MouseWheelEvent,    "Nenuphar.Event.Mouse.Mouse-Wheel")
        NPSignal(OnButtonPressed,   MouseButtonEvent,   "Nenuphar.Event.Mouse.Button-Pressed")
        NPSignal(OnButtonRelease,   MouseButtonEvent,   "Nenuphar.Event.Mouse.Button-Release")
        NPSignal(OnMouseMove,       MouseMoveEvent,     "Nenuphar.Event.Mouse-Motion")
        NPSignal(OnKeyDown,         KeyEvent,           "Nenuphar.Event.Key.Key-Down")
        NPSignal(OnKeyRelease,      KeyEvent,           "Nenuphar.Event.Key.Key-Release")
        NPSignal(OnKeyPressed,      KeyEvent,           "Nenuphar.Event.Key.Key-Pressed")
    };

}
