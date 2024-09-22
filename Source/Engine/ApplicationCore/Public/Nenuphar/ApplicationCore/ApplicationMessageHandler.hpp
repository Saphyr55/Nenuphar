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

        virtual void OnWindowResize(SharedRef<Window> window)
        {
        }

        virtual void OnMouseWheel(SharedRef<Window> window, Float Delta, Float PosX, Float PosY)
        {
        }

        virtual void OnMouseWheel(Float Delta, Float PosX, Float PosY)
        {
        }

        virtual void OnKeyUp(SharedRef<Window> window, Input::Key key)
        {
        }

        virtual void OnKeyUp(Input::Key key)
        {
        }

        virtual void OnKeyDown(SharedRef<Window> window, Input::Key key)
        {
        }

        virtual void OnKeyDown(Input::Key key)
        {
        }

        virtual void OnButtonUp(SharedRef<Window> window, Input::Button Button, UInt Clicks)
        {
        }

        virtual void OnButtonUp(Input::Button Button, UInt Clicks)
        {
        }

        virtual void OnButtonDown(SharedRef<Window> window, Input::Button Button, UInt Clicks)
        {
        }

        virtual void OnButtonDown(Input::Button Button, UInt Clicks)
        {
        }

        virtual void OnMouseMove(Float PosRelX, Float PosRelY, Float PosX, Float PosY)
        {
        }
    };

}// namespace Nenuphar