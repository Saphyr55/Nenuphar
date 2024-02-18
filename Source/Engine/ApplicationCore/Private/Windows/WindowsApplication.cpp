#include "Nenuphar/ApplicationCore/Windows/WindowsApplication.hpp"

#include <ranges>

#include <fmt/format.h>

#include "Nenuphar/ApplicationCore/Windows/WindowsWindow.hpp"
#include "Nenuphar/Core.hpp"

namespace Nenuphar
{

    WindowsApplication* WindowsApplication::WindowsApp = nullptr;

    WindowsApplication::WindowsApplication(HINSTANCE hinstance)
        : hinstance(hinstance)
        , isRunning(true)
    {
        Initialize();
        WindowsApp = this;
    }

    WindowsApplication::~WindowsApplication() = default;

    EventBus& WindowsApplication::GetEventBus()
    {
        return eventBus;
    }

    void WindowsApplication::Stop()
    {
        isRunning = false;
    }

    HINSTANCE WindowsApplication::GetHInstance() const
    {
        return hinstance;
    }

    bool WindowsApplication::IsRunning() const
    {
        return isRunning;
    }

    void WindowsApplication::SetRunning(const bool is)
    {
        isRunning = is;
    }

    Int CALLBACK WindowsApplication::ProcessMessage(HWND hwnd, UInt msg, WPARAM wParam, LPARAM lParam)
    {
        switch (msg)
        {
            case WM_SYSKEYDOWN:
            case WM_KEYDOWN:
            {
                KeyEvent e{};
                e.Key = static_cast<Input::Key>(wParam);

                if ((HIWORD(lParam) & KF_REPEAT) != KF_REPEAT)
                {
                    Emit(hwnd, [this, &e](const SharedRef<Window>& window)
                        {
                        window->GetWindowEventHandler().EmitOnKeyPressed(eventBus, e);
                    });
                }

                Emit(hwnd, [this, &e](const SharedRef<Window>& window)
                {
                    window->GetWindowEventHandler().EmitOnKeyDown(eventBus, e);
                });
                break;
            }
            case WM_LBUTTONUP:
            {
                constexpr auto button = Input::Button::Left;
                constexpr MouseButtonEvent e(button);
                Emit(hwnd, [this, &e](const SharedRef<Window>& window)
                {
                    window->GetWindowEventHandler().EmitOnButtonRelease(eventBus, e);
                });
                break;
            }
            case WM_MBUTTONUP:
            {
                constexpr auto button = Input::Button::Middle;
                constexpr MouseButtonEvent e(button);
                Emit(hwnd, [this, &e](const SharedRef<Window>& window)
                {
                    window->GetWindowEventHandler().EmitOnButtonRelease(eventBus, e);
                });
                break;
            }
            case WM_RBUTTONUP:
            {
                constexpr auto button = Input::Button::Right;
                constexpr MouseButtonEvent e(button);
                Emit(hwnd, [this, &e](const SharedRef<Window>& window)
                {
                    window->GetWindowEventHandler().EmitOnButtonRelease(eventBus, e);
                });
                break;
            }
            case WM_LBUTTONDOWN:
            {
                constexpr auto button = Input::Button::Left;
                constexpr MouseButtonEvent e(button);
                Emit(hwnd, [this, &e](const SharedRef<Window>& window)
                {
                    window->GetWindowEventHandler().EmitOnButtonPressed(eventBus, e);
                });
                break;
            }
            case WM_MBUTTONDOWN:
            {
                constexpr auto button = Input::Button::Middle;
                constexpr MouseButtonEvent e(button);
                Emit(hwnd, [this, &e](const SharedRef<Window>& window)
                {
                    window->GetWindowEventHandler().EmitOnButtonPressed(eventBus, e);
                });
                break;
            }
            case WM_RBUTTONDOWN:
            {
                constexpr auto button = Input::Button::Right;
                constexpr MouseButtonEvent e(button);
                Emit(hwnd, [this, &e](const SharedRef<Window>& window)
                {
                    window->GetWindowEventHandler().EmitOnButtonPressed(eventBus, e);
                });
                break;
            }
            case WM_XBUTTONDOWN:
            case WM_XBUTTONUP:
            {

                Input::Button button;
                if (GET_XBUTTON_WPARAM(wParam) == XBUTTON1)
                {
                    button = Input::Button::XButton1;
                }
                else
                {
                    button = Input::Button::XButton2;
                }

                const MouseButtonEvent e(button);

                for (const auto& [_, window] : windowRegistry)
                {
                    if (msg == WM_XBUTTONDOWN)
                    {
                        if (window->GetOSWindowHandle() == hwnd)
                            window->GetWindowEventHandler().EmitOnButtonPressed(eventBus, e);
                    }
                    else
                    {
                        if (window->GetOSWindowHandle() == hwnd)
                            window->GetWindowEventHandler().EmitOnButtonRelease(eventBus, e);
                    }
                }

                break;
            }
            case WM_SYSKEYUP:
            case WM_KEYUP:
            {
                const KeyEvent e(static_cast<Input::Key>(wParam));
                Emit(hwnd, [this, &e](const SharedRef<Window>& window)
                {
                    window->GetWindowEventHandler().EmitOnKeyRelease(eventBus, e);
                });
                break;
            }
            case WM_NCMOUSEMOVE:
            case WM_MOUSEMOVE:
            {
                const Float x = GET_X_LPARAM(lParam);
                const Float y = GET_Y_LPARAM(lParam);
                const MouseMoveEvent e(x, y, x, y);
                Emit(hwnd, [this, &e](const SharedRef<Window>& window)
                {
                    window->GetWindowEventHandler().EmitOnMouseMove(eventBus, e);
                });
                break;
            }
            case WM_MOUSEWHEEL:
            {
                const Float delta = GET_WHEEL_DELTA_WPARAM(wParam);
                const Float x = GET_X_LPARAM(lParam);
                const Float y = GET_Y_LPARAM(lParam);
                const MouseWheelEvent e(delta, y, x);
                Emit(hwnd, [this, &e](const SharedRef<Window>& window)
                {
                    window->GetWindowEventHandler().EmitOnMouseWheel(eventBus, e);
                });
                break;
            }
            case WM_CLOSE:
            {
                CloseEvent windowCloseEvent;
                UInt16 ID = 0;
                for (const auto& [_, window] : windowRegistry)
                {
                    if (window->GetOSWindowHandle() == hwnd)
                    {
                        window->Destroy();
                        ID = window->GetID();
                        window->GetWindowEventHandler().EmitOnClose(eventBus, windowCloseEvent);
                        NP_INFO(WindowsWindow, "The window ID={}, HWND={} is closed.", ID, fmt::ptr(hwnd));
                        break;
                    }
                }
                if (ID > 0)
                {
                    const auto it = windowRegistry.find(ID);
                    windowRegistry.erase(it);
                }
                break;
            }
            case WM_DESTROY:
            {
                PostQuitMessage(0);
                return 0;
            }
            default:
                return DefWindowProc(hwnd, msg, wParam, lParam);
        }
        return DefWindowProc(hwnd, msg, wParam, lParam);
    }

    void WindowsApplication::Emit(HWND handle, std::function<void(SharedRef<Window>)> func)
    {
        for (const auto& [_, window] : windowRegistry)
        {
            if (window->GetOSWindowHandle() == handle)
                func(window);
        }
    }

    LRESULT WndProcImpl(HWND hwnd, UInt msg, WPARAM wParam, LPARAM lParam)
    {
        return WindowsApplication::WindowsApp->ProcessMessage(hwnd, msg, wParam, lParam);
    }

    LRESULT CALLBACK WindowsApplication::WndProc(HWND hwnd, UInt msg, WPARAM wParam, LPARAM lParam)
    {
        return WndProcImpl(hwnd, msg, wParam, lParam);
    }

    void WindowsApplication::Initialize() const
    {
        WNDCLASSEX wcex;
        wcex.cbSize         = sizeof(WNDCLASSEX);
        wcex.style          = CS_HREDRAW | CS_VREDRAW;
        wcex.lpfnWndProc    = WndProc;
        wcex.cbClsExtra     = 0;
        wcex.cbWndExtra     = 0;
        wcex.hInstance      = hinstance;
        wcex.hIcon          = LoadIcon(hinstance, IDI_APPLICATION);
        wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
        wcex.hbrBackground  = reinterpret_cast<HBRUSH>(COLOR_WINDOW + 1);
        wcex.lpszMenuName   = nullptr;
        wcex.lpszClassName  = WindowsWindow::ApplicationWindowClassName;
        wcex.hIconSm        = LoadIcon(hinstance, IDI_APPLICATION);

        if (!RegisterClassEx(&wcex))
        {
            NP_ERROR(WindowsWindow, "Call to RegisterClassEx failed!");
            return;
        }

        NP_INFO(WindowsWindow, "Windows Application Instance has been registed.");
        NP_INFO(WindowsWindow, "Nenuphar Application was started with a windows instance.");
    }

    void WindowsApplication::Destroy() const
    {
        UnregisterClass
        (
            WindowsWindow::ApplicationWindowClassName,
            hinstance
        );
    }

}
