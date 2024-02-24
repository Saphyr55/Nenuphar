#pragma once

#include "Nenuphar/InputSystem/Button.hpp"
#include "Nenuphar/InputSystem/Key.hpp"

namespace Nenuphar
{

    struct MouseButtonEvent
	{
        Input::Button Button;
        UInt Clicks;
    };

    struct MouseMoveEvent
	{
		Float PosRelX;
		Float PosRelY;
		Float PosX;
		Float PosY;
    };

    struct MouseWheelEvent
	{
        Float Delta;
        Float PosX;
        Float PosY;
    };

	struct KeyEvent
	{
        Input::Key Key;
	};

} 
