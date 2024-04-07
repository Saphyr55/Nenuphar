#include "Nenuphar/ApplicationCore/Window.hpp"
#include "Nenuphar/ApplicationCore/WindowBase.hpp"

namespace Nenuphar
{

    const WindowEventHandler& Window::GetWindowEventHandler() const
    {
        return m_base->GetWindowEventHandler();
    }

    WindowID Window::GetID() const
    {
        return m_base->GetID();
    }

    Window::Window(const WindowDefinition& definition, PlatformApplication& app)
        : m_base(WindowBase::Create(definition, app))
    {
    }

    Window::Window(
        const StringView title,
        const Int width,
        const Int height
        )
        : Window(WindowDefinition{
                String(title),
                static_cast<Float>(width),
                static_cast<Float>(height)})
    {
    }

    Void Window::PoolEvent() const
    {
        m_base->PoolEvent();
    }

    Bool Window::IsWindowMaximized() const
    {
        return m_base->IsWindowMaximized();
    }

    Bool Window::IsWindowMinimized() const
    {
        return m_base->IsWindowMinimized();
    }

    Bool Window::IsVisible() const
    {
        return m_base->IsVisible();
    }

    Void* Window::GetOSWindowHandle() const
    {
        return m_base->GetOSWindowHandle();
    }

    Void Window::Hide()
    {
        m_base->Hide();
    }

    Void Window::Show()
    {
        m_base->Show();
    }

    Void Window::Restore()
    {
        m_base->Restore();
    }

    Void Window::Maximize()
    {
        m_base->Maximize();
    }

    Void Window::Destroy()
    {
        m_base->Destroy();
    }

    Void Window::ReshapeWindow(Int width, Int height)
    {
        m_base->ReshapeWindow(width, height);
    }

    Void Window::SetTitle(StringView title)
    {
        m_base->SetTitle(title);
    }

    const WindowSignals& Window::GetWindowSignals() const
    {
        return m_base->GetWindowSignals();
    }
}
