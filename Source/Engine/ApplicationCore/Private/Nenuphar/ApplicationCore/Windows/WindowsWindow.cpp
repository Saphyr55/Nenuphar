#include "Nenuphar/ApplicationCore/Windows/WindowsWindow.hpp"
#include "Nenuphar/ApplicationCore/Windows/WindowsApplication.hpp"
#include "Nenuphar/Core/Logger/Logger.hpp"
#include <cstdlib>
#include <winuser.h>

#if NP_PLATFORM_WINDOWS

#include <fmt/format.h>

namespace Nenuphar
{

    WindowID WindowsWindow::LastID = 0;

    WindowsWindow::WindowsWindow(WindowsApplication& application,
                                 const WindowDefinition& definition)
        : m_definition(definition)
        , m_windowsApplication(application)
        , m_hwnd(NULL)
        , ID(++LastID)
    {
        InitializeWindowHandle();

        if (IsValid())
        {
            NP_INFO(WindowsWindow, "Windows window was created successfully.");
            NP_DEBUG(WindowsWindow, "Windows window configuration : ");
            NP_DEBUG(WindowsWindow, "      ID = {}", ID);
            NP_DEBUG(WindowsWindow, "      HWND = {}", fmt::ptr(m_hwnd));
            NP_DEBUG(WindowsWindow, "      Width = {}", m_definition.Width);
            NP_DEBUG(WindowsWindow, "      Height = {}", m_definition.Height);
            NP_DEBUG(WindowsWindow, "      Title = {}", m_definition.Title);
        }
        else
        {
            NP_CRITICAL(WindowsWindow, "Call to CreateWindow failed, enable to create windows window.");
        }
    }

    WindowsWindow::~WindowsWindow()
    {
    }

    void WindowsWindow::InitializeWindowHandle()
    {
        if (IsValid())
        {
            return;
        }

        m_hwnd = CreateWindowEx(
                WS_EX_OVERLAPPEDWINDOW,
                WindowsApplication::ApplicationClassName,
                m_definition.Title.c_str(),
                WS_OVERLAPPEDWINDOW,
                CW_USEDEFAULT,
                CW_USEDEFAULT,
                static_cast<Int>(m_definition.Width),
                static_cast<Int>(m_definition.Height),
                nullptr,
                nullptr,
                m_windowsApplication.GetHInstance(),
                nullptr
                );
    }

    bool WindowsWindow::IsWindowMaximized() const
    {
        // TODO: IsWindowMaximized
        return false;
    }

    bool WindowsWindow::IsWindowMinimized() const
    {
        // TODO: IsWindowMinimized
        return false;
    }

    bool WindowsWindow::IsVisible() const
    {
        // TODO: IsVisible
        return false;
    }

    void* WindowsWindow::GetOSWindowHandle() const
    {
        return m_hwnd;
    }

    void WindowsWindow::Hide()
    {
        ::ShowWindow(m_hwnd, SW_HIDE);
    }

    void WindowsWindow::Show()
    {
        ::ShowWindow(m_hwnd, SW_NORMAL);
    }

    void WindowsWindow::Restore()
    {
        ::ShowWindow(m_hwnd, SW_RESTORE);
    }

    void WindowsWindow::Maximize()
    {
        ::ShowWindow(m_hwnd, SW_SHOWMAXIMIZED);
    }

    void WindowsWindow::Destroy()
    {
        if (m_hwnd)
        {
            ::DestroyWindow(m_hwnd);
        }
    }

    void WindowsWindow::ReshapeWindow(Int width, Int height)
    {
        // TODO: Reshape window.
    }

    void WindowsWindow::SetTitle(StringView title)
    {
        // TODO: SetTitle window.
    }

    HWND WindowsWindow::GetHWND()
    {
        return m_hwnd;
    }

    bool WindowsWindow::IsValid() 
    {
        return m_hwnd;
    }

    const WindowDefinition& WindowsWindow::GetWindowDefinition() const
    {
        return m_definition;
    }

    WindowID WindowsWindow::GetID() const
    {
        return ID;
    }

}// namespace Nenuphar

#endif
