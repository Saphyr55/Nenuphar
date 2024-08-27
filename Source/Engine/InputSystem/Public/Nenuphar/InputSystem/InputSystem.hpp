#pragma once

#include <unordered_set>

#include "Nenuphar/InputSystem/Button.hpp"

namespace Nenuphar
{

    struct InputSystem
    {
        static bool IsButtonDown(Input::Button button);

        static std::unordered_set<Input::Button> DownButtons;
    };

}