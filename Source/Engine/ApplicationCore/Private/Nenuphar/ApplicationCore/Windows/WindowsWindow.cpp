#include "Nenuphar/ApplicationCore/Windows/WindowsWindow.hpp"
#include "Nenuphar/ApplicationCore/Windows/WindowsApplication.hpp"
#include "Nenuphar/Common/Instanciate.hpp"
#include "Nenuphar/Core/Logger/Logger.hpp"
#include "Nenuphar/InputSystem/Button.hpp"
#include "Nenuphar/InputSystem/Event.hpp"
#include "Nenuphar/InputSystem/InputSystem.hpp"
#include <cstdlib>
#include <winuser.h>


#if NP_PLATFORM_WINDOWS

#include <fmt/format.h>

namespace Nenuphar
{

    WindowID WindowsWindow::LastID = 0;

    Void WindowsWindow::PoolEvent() const
    {
        MSG msg;
        while (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    WindowID WindowsWindow::GetID() const
    {
        return ID;
    }

    HWND WindowsWindow::Initialize()
    {
        hwnd = CreateWindowEx(
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
                windowsApplication.GetHInstance(),
                nullptr);

        if (!hwnd)
        {
            NP_CRITICAL(WindowsWindow, "Call to CreateWindow failed, enable to create windows window.");
            return hwnd;
        }

        return hwnd;
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
        return hwnd;
    }

    void WindowsWindow::Hide()
    {
        ShowWindow(hwnd, SW_HIDE);
    }

    void WindowsWindow::Show()
    {
        ShowWindow(hwnd, SW_NORMAL);
    }

    void WindowsWindow::Restore()
    {
        ShowWindow(hwnd, SW_RESTORE);
    }

    void WindowsWindow::Maximize()
    {
        ShowWindow(hwnd, SW_SHOWMAXIMIZED);
    }

    void WindowsWindow::Destroy()
    {
        if (hwnd)
        {
            DestroyWindow(hwnd);
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

    WindowsWindow::WindowsWindow(WindowsApplication& inApplication,
                                 WindowDefinition inDefinition)
        : m_definition(inDefinition)
        , windowsApplication(inApplication)
        , hwnd(Initialize())
        , ID(++LastID)
    {

        if (hwnd)
        {
            NP_INFO(WindowsWindow, "Windows window was created successfully.");
            NP_DEBUG(WindowsWindow, "Windows window configuration : ");
            NP_DEBUG(WindowsWindow, "      ID = {}", ID);
            NP_DEBUG(WindowsWindow, "      HWND = {}", fmt::ptr(hwnd));
            NP_DEBUG(WindowsWindow, "      Width = {}", m_definition.Width);
            NP_DEBUG(WindowsWindow, "      Height = {}", m_definition.Height);
            NP_DEBUG(WindowsWindow, "      Title = {}", m_definition.Title);
        }
        else
        {
            throw std::runtime_error("Can't create windows window.");
        }

        m_windowSignals.OnButtonDown().ConnectHandler([](const MouseButtonEvent& event) {
            InputSystem::DownButtons.insert(event.Button);
        });

        m_windowSignals.OnButtonRelease().ConnectHandler([](const MouseButtonEvent& event) {
            InputSystem::DownButtons.erase(event.Button);
        });
    }

    WindowsWindow::~WindowsWindow()
    {
        Destroy();
    }

    Int WindowsWindow::ProcessEvent(MSG msg)
    {
        auto& message = msg.message;
        auto& wParam = msg.wParam;
        auto& lParam = msg.lParam;

        return DefWindowProc(hwnd, message, wParam, lParam);
    }

    HWND WindowsWindow::GetHWND()
    {
        return hwnd;
    }

    const WindowSignals& WindowsWindow::GetWindowSignals() const
    {
        return m_windowSignals;
    }

    const WindowDefinition& WindowsWindow::GetWindowDefinition() const
    {
        return m_definition;
    }

}// namespace Nenuphar

#endif
