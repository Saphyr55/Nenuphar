#pragma once

#include "Nenuphar/ApplicationCore/Window.hpp"
#include "Nenuphar/Common/Type/Type.hpp"
#include "Nenuphar/InputSystem/Button.hpp"
#include "Nenuphar/InputSystem/Key.hpp"


namespace Nenuphar
{


    class ApplicationMessageHandler
    {
    public:
        virtual void OnWindowClose(SharedRef<Window> window)
        {
        }

        virtual void OnWindowResize(SharedRef<Window> window, UInt width, UInt height)
        {
        }

        virtual void OnMouseWheel(Float delta)
        {
        }

        virtual void OnKeyUp(Input::Key key)
        {
        }

        virtual void OnKeyDown(Input::Key key)
        {
        }

        virtual void OnButtonUp(Input::Button button)
        {
        }

        virtual void OnButtonDown(Input::Button button)
        {
        }

        virtual void OnMouseMove(Float posRelX, Float posRelY, Float posX, Float posY)
        {
        }
    };

}// namespace Nenuphar