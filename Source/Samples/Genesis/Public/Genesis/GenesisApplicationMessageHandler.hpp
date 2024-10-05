#pragma once

#include "Genesis/Genesis.hpp"
#include "Nenuphar/ApplicationCore/Application.hpp"
#include "Nenuphar/ApplicationCore/ApplicationMessageHandler.hpp"
#include "Nenuphar/Common/Type/Type.hpp"
#include "Nenuphar/InputSystem/Event.hpp"

#include "Nenuphar/InputSystem/InputSystem.hpp"
#include "WindowEventHandler.hpp"

namespace Np = Nenuphar;

class GenesisApplicationMessageHandler : public Np::ApplicationMessageHandler
{
public:
    virtual void OnWindowClose(Np::SharedRef<Np::Window> window) override
    {
        if (m_windowEventHandler->GetWindow() != window)
        {
            return;
        }

        Np::CloseEvent event;
        event.Window = window;
        m_windowEventHandler->OnClose().Emit(event);
    }

    virtual void OnWindowResize(Np::SharedRef<Np::Window> window,
                                Np::UInt width,
                                Np::UInt height) override
    {
        if (window != m_windowEventHandler->GetWindow())
        {
            return;
        }

        window->GetWindowDefinition().Width = width;
        window->GetWindowDefinition().Height = height;

        Np::ResizeEvent event;
        event.Width = width;
        event.Height = height;
        event.Window = window;
        m_windowEventHandler->OnResize().Emit(event);
    }

    virtual void OnKeyUp(Np::Input::Key key) override
    {
        Np::KeyEvent event;
        event.Key = key;
        m_windowEventHandler->OnKeyDown().Emit(event);
    }

    virtual void OnKeyDown(Np::Input::Key key) override
    {
        Np::KeyEvent event;
        event.Key = key;
        m_windowEventHandler->OnKeyDown().Emit(event);
    }

    virtual void OnButtonUp(Np::Input::Button button) override
    {
        Np::InputSystem::DownButtons.erase(button);

        Np::MouseButtonEvent event;
        event.Button = button;
        event.Clicks = 1;
        m_windowEventHandler->OnButtonUp().Emit(event);
    }

    virtual void OnButtonDown(Np::Input::Button button) override
    {
        Np::InputSystem::DownButtons.insert(button);

        Np::MouseButtonEvent event;
        event.Button = button;
        event.Clicks = 1;
        m_windowEventHandler->OnButtonDown().Emit(event);
    }

    virtual void OnMouseWheel(Np::Float delta) override
    {
        Np::MouseWheelEvent event;
        event.Delta = delta;
        m_windowEventHandler->OnMouseWheel().Emit(event);
    }

    virtual void OnMouseMove(Np::Float posRelX,
                             Np::Float posRelY,
                             Np::Float posX,
                             Np::Float posY) override
    {
        Np::MouseMoveEvent event;
        event.PosRelX = posRelX;
        event.PosRelY = posRelY;
        event.PosX = posX;
        event.PosY = posY;
        m_windowEventHandler->OnMouseMove().Emit(event);
    }

public:
    explicit GenesisApplicationMessageHandler(Np::SharedRef<WindowEventHandler> windowEventHandler)
        : m_windowEventHandler(windowEventHandler)
    {
    }

private:
    Np::SharedRef<WindowEventHandler> m_windowEventHandler;
};