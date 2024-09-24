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

        virtual void OnMouseWheel(Float Delta)
        {
        }

        virtual void OnKeyUp(Input::Key key)
        {
        }

        virtual void OnKeyDown(Input::Key key)
        {
        }

        virtual void OnButtonUp(Input::Button Button)
        {
        }

        virtual void OnButtonDown(Input::Button Button)
        {
        }

        virtual void OnMouseMove(Float PosRelX, Float PosRelY, Float PosX, Float PosY)
        {
        }
    };

}// namespace Nenuphar