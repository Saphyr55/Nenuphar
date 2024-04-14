#pragma once

#include <unordered_set>

#include "Nenuphar/Common/Type/Type.hpp"
#include "Nenuphar/InputSystem/Button.hpp"
#include "Nenuphar/EventSystem/Signal.hpp"

namespace Nenuphar
{

    struct InputSystem
    {
        static bool IsButtonDown(Input::Button button);

        static std::unordered_set<Input::Button> DownButtons;
    };

}