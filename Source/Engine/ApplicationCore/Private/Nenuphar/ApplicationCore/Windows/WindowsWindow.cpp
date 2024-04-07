#include <utility>

#include <fmt/format.h>

#include "Nenuphar/ApplicationCore/Windows/WindowsWindow.hpp"
#include "Nenuphar/ApplicationCore/Windows/WindowsApplication.hpp"
#include "Nenuphar/Core/Core.hpp"
#include "Nenuphar/Common/Instanciate.hpp"

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

    const WindowEventHandler& WindowsWindow::GetWindowEventHandler() const
    {
        return windowEventHandler;
    }

    HWND WindowsWindow::Initialize()
    {
        hwnd = CreateWindowEx
        (
            WS_EX_OVERLAPPEDWINDOW,
            WindowsApplication::ApplicationClassName,
            definition.Title.c_str(),
            WS_OVERLAPPEDWINDOW,
            CW_USEDEFAULT,
            CW_USEDEFAULT,
            static_cast<Int>(definition.Width),
            static_cast<Int>(definition.Height),
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
        : definition(inDefinition)
        , windowsApplication(inApplication)
        , hwnd(Initialize())
        , ID(++LastID)
        , windowEventHandler(ID, eventBus)
    {

        if (hwnd)
        {
            WindowsApplication::WindowsWindowRegistry.emplace(hwnd, this);
            NP_INFO(WindowsWindow,  "Windows window was created sucessfully.");
            NP_DEBUG(WindowsWindow, "Windows window configuration : ");
            NP_DEBUG(WindowsWindow, "      ID = {}", ID);
            NP_DEBUG(WindowsWindow, "      HWND = {}", fmt::ptr(hwnd));
            NP_DEBUG(WindowsWindow, "      Width = {}", definition.Width);
            NP_DEBUG(WindowsWindow, "      Height = {}", definition.Height);
            NP_DEBUG(WindowsWindow, "      Title = {}", definition.Title);
        }
        else
        {
            throw std::runtime_error("Can't create windows window.");
        }

    }

    Int WindowsWindow::ProcessEvent(MSG msg)
    {
        const UINT message = msg.message;
        auto& wParam = msg.wParam;
        auto& lParam = msg.lParam;

        switch (message)
        {
        case WM_SIZE:
        {
            windowEventHandler.EmitOnResize({ 0, 0 });
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
                windowEventHandler.EmitOnKeyPressed(e);
            }

            windowEventHandler.EmitOnKeyDown(e);
            break;
        }
        case WM_LBUTTONUP:
        {
            constexpr auto button = Input::Button::Left;
            constexpr MouseButtonEvent e(button);
            windowEventHandler.EmitOnButtonRelease(e);
            break;
        }
        case WM_MBUTTONUP:
        {
            constexpr auto button = Input::Button::Middle;
            constexpr MouseButtonEvent e(button);
            windowEventHandler.EmitOnButtonRelease(e);
            break;
        }
        case WM_RBUTTONUP:
        {
            constexpr auto button = Input::Button::Right;
            constexpr MouseButtonEvent e(button);
            windowEventHandler.EmitOnButtonRelease(e);
            break;
        }
        case WM_LBUTTONDOWN:
        {
            constexpr auto button = Input::Button::Left;
            constexpr MouseButtonEvent e(button);
            windowEventHandler.EmitOnButtonPressed(e);
            break;
        }
        case WM_MBUTTONDOWN:
        {
            constexpr auto button = Input::Button::Middle;
            constexpr MouseButtonEvent e(button);
            windowEventHandler.EmitOnButtonPressed(e);
            break;
        }
        case WM_RBUTTONDOWN:
        {
            constexpr auto button = Input::Button::Right;
            constexpr MouseButtonEvent e(button);
            windowEventHandler.EmitOnButtonPressed(e);
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
                windowEventHandler.EmitOnButtonPressed(e);
            }
            else
            {
                windowEventHandler.EmitOnButtonRelease(e);
            }
            break;
        }
        case WM_SYSKEYUP:
        case WM_KEYUP:
        {
            const KeyEvent e(static_cast<Input::Key>(wParam));
            windowEventHandler.EmitOnKeyRelease(e);
            break;
        }
        case WM_NCMOUSEMOVE:
        case WM_MOUSEMOVE:
        {
            const Float x = GET_X_LPARAM(lParam);
            const Float y = GET_Y_LPARAM(lParam);
            const MouseMoveEvent e(x, y, x, y);
            windowEventHandler.EmitOnMouseMove(e);
            break;
        }
        case WM_MOUSEWHEEL:
        {
            const Float delta = GET_WHEEL_DELTA_WPARAM(wParam);
            const Float x = GET_X_LPARAM(lParam);
            const Float y = GET_Y_LPARAM(lParam);
            const MouseWheelEvent e(delta, y, x);
            windowEventHandler.EmitOnMouseWheel(e);
            break;
        }
        case WM_CLOSE:
        {
            NP_INFO(WindowsWindow, "The window ID={}, HWND={} closed.", ID, fmt::ptr(hwnd));
            windowEventHandler.EmitOnClose({});
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
}
