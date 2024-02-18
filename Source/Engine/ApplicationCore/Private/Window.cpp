#include "Nenuphar/ApplicationCore/Window.hpp"
#include "Nenuphar/ApplicationCore/WindowBase.hpp"

namespace Nenuphar
{

    const WindowEventHandler& Window::GetWindowEventHandler() const
    {
        return base->GetWindowEventHandler();
    }

    WindowID Window::GetID() const
    {
        return base->GetID();
    }

    Window::Window(WindowDefinition definition)
        : base(WindowBase::Create(definition))
    {
    }

    Void Window::PoolEvent() const
    {
        base->PoolEvent();
    }

    Bool Window::IsWindowMaximized() const
    {
        return base->IsWindowMaximized();
    }

    Bool Window::IsWindowMinimized() const
    {
        return base->IsWindowMinimized();
    }

    Bool Window::IsVisible() const
    {
        return base->IsVisible();
    }

    Void* Window::GetOSWindowHandle() const
    {
        return base->GetOSWindowHandle();
    }

    Void Window::Hide()
    {
        base->Hide();
    }

    Void Window::Show()
    {
        base->Show();
    }

    Void Window::Restore()
    {
        base->Restore();
    }

    Void Window::Maximaze()
    {
        base->Maximaze();
    }

    Void Window::Destroy()
    {
        base->Destroy();
    }

    Void Window::ReshapeWindow(Int width, Int height)
    {
        base->ReshapeWindow(width, height);
    }

    Void Window::SetTitle(StringView title)
    {
        base->SetTitle(title);
    }
}
