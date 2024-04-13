#include "Nenuphar/InputSystem/InputSystem.hpp"
#include "Nenuphar/EventSystem/EventSystem.hpp"

namespace Nenuphar
{

    std::unordered_set<Input::Button> InputSystem::DownButtons = { };

    bool InputSystem::IsButtonDown(Input::Button button)
    {
        return DownButtons.find(button) != DownButtons.end();
    }

}