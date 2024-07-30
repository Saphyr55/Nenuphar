#include <fmt/format.h>

#include "Nenuphar/Core/Core.hpp"
#include "Nenuphar/ApplicationCore/Windows/WindowsWindow.hpp"
#include "Nenuphar/InputSystem/InputSystem.hpp"

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
        hwnd = CreateWindowEx
        (
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
                nullptr
        );

        if (!hwnd)
        {
            NP_ERROR(WindowsWindow, "Call to CreateWindow failed, enable to create windows window.");
            return hwnd;
        }

        return hwnd;
    }

    bool WindowsWindow::IsWindowMaximized() const
    {
        return false;
    }

    bool WindowsWindow::IsWindowMinimized() const
    {
        return false;
    }

    bool WindowsWindow::IsVisible() const
    {
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
        if (hwnd != nullptr)
        {
            DestroyWindow(hwnd);
            hwnd = nullptr;
        }
    }

    void WindowsWindow::ReshapeWindow(Int width, Int height)
    {
    }

    void WindowsWindow::SetTitle(StringView title)
    {
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
            WindowsApplication::WindowsWindowRegistry.emplace(hwnd, this);
            NP_INFO(WindowsWindow,  "Windows window was created successfully.");
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

        m_windowSignals.OnButtonDown().ConnectHandler(
                [](auto& evt)
                {
                    InputSystem::DownButtons.insert(evt.Button);
                });

        m_windowSignals.OnButtonRelease().ConnectHandler(
                [](auto& evt)
                {
                    InputSystem::DownButtons.erase(evt.Button);
                });
    }

    Int WindowsWindow::ProcessEvent(MSG msg)
    {

        auto& message = msg.message;
        auto& wParam = msg.wParam;
        auto& lParam = msg.lParam;

        switch (message)
        {
        case WM_SIZE:
        {
            auto width =  Float(LOWORD(lParam));
            auto height =  Float(HIWORD(lParam));
            m_definition.Width = width;
            m_definition.Height = height;
            m_windowSignals.EmitOnResize(ResizeEvent(width, height));
            break;
        }
        case WM_PAINT:
        {
            break;
        }
        case WM_SYSKEYDOWN:
        case WM_KEYDOWN:
        {
            KeyEvent e{};
            e.Key = static_cast<Input::Key>(wParam);

            if ((HIWORD(lParam) & KF_REPEAT) != KF_REPEAT)
            {
                m_windowSignals.EmitOnKeyPressed(e);
            }

            m_windowSignals.EmitOnKeyDown(e);
            break;
        }
        case WM_LBUTTONUP:
        {
            constexpr auto button = Input::Button::Left;
            constexpr MouseButtonEvent e(button);
            m_windowSignals.EmitOnButtonRelease(e);
            break;
        }
        case WM_MBUTTONUP:
        {
            constexpr auto button = Input::Button::Middle;
            constexpr MouseButtonEvent e(button);
            m_windowSignals.EmitOnButtonRelease(e);
            break;
        }
        case WM_RBUTTONUP:
        {
            constexpr auto button = Input::Button::Right;
            constexpr MouseButtonEvent e(button);
            m_windowSignals.EmitOnButtonRelease(e);
            break;
        }
        case WM_LBUTTONDOWN:
        {
            constexpr auto button = Input::Button::Left;
            constexpr MouseButtonEvent e(button);
            m_windowSignals.EmitOnButtonDown(e);
            break;
        }
        case WM_MBUTTONDOWN:
        {
            constexpr auto button = Input::Button::Middle;
            constexpr MouseButtonEvent e(button);
            m_windowSignals.EmitOnButtonDown(e);
            break;
        }
        case WM_RBUTTONDOWN:
        {
            constexpr auto button = Input::Button::Right;
            constexpr MouseButtonEvent e(button);
            m_windowSignals.EmitOnButtonDown(e);
            break;
        }
        case WM_XBUTTONDOWN:
        case WM_XBUTTONUP:
        {
            const auto button = GET_XBUTTON_WPARAM(wParam) == XBUTTON1
                ? Input::Button::XButton1
                : Input::Button::XButton2;

            const MouseButtonEvent e(button);
            if (message == WM_XBUTTONDOWN)
            {
                m_windowSignals.EmitOnButtonDown(e);
            }
            else
            {
                m_windowSignals.EmitOnButtonRelease(e);
            }
            break;
        }
        case WM_SYSKEYUP:
        case WM_KEYUP:
        {
            const KeyEvent e(static_cast<Input::Key>(wParam));
            m_windowSignals.EmitOnKeyRelease(e);
            break;
        }
        case WM_NCMOUSEMOVE:
        case WM_MOUSEMOVE:
        {
            static Float lastMouseX = 0;
            static Float lastMouseY = 0;
            const Float x = GET_X_LPARAM(lParam);
            const Float y = GET_Y_LPARAM(lParam);
            const Float relX = x - lastMouseX;
            const Float relY = y - lastMouseY;
            const MouseMoveEvent e(relX, relY, x, y);
            lastMouseX = x;
            lastMouseY = y;
            m_windowSignals.EmitOnMouseMove(e);
            break;
        }
        case WM_MOUSEWHEEL:
        {
            const Float delta = GET_WHEEL_DELTA_WPARAM(wParam);
            const Float x = GET_X_LPARAM(lParam);
            const Float y = GET_Y_LPARAM(lParam);
            const MouseWheelEvent e(delta, y, x);
            m_windowSignals.EmitOnMouseWheel(e);
            break;
        }
        case WM_CLOSE:
        {
            CloseEvent closeEvent;
            NP_INFO(WindowsWindow, "The window ID={}, HWND={} closed.", ID, fmt::ptr(hwnd));
            m_windowSignals.EmitOnClose(closeEvent);
            break;
        }
        case WM_DESTROY:
        {
            PostQuitMessage(0);
            return 0;
        }
        default:
            break;
        }

        return DefWindowProc(hwnd, message, wParam, lParam);
    }

    const WindowSignals& WindowsWindow::GetWindowSignals() const
    {
        return m_windowSignals;
    }

    const WindowDefinition& WindowsWindow::GetWindowDefinition() const
    {
        return m_definition;
    }

}
