#include "Nenuphar/ApplicationCore/Windows/WindowsApplication.hpp"
#include "Nenuphar/ApplicationCore/Windows/WindowsWindow.hpp"
#include "Nenuphar/Core.hpp"

namespace Nenuphar
{

    SharedRef<WindowsApplication> WindowsApplication::WindowsApp;

    WindowsApplication::WindowsApplication(HINSTANCE hinstance)
        : hinstance(hinstance)
        , handlers({ })
        , isRunning(true)
    {
        WindowsApp = SharedRef<WindowsApplication>(this);
    }

    WindowEventHandler& WindowsApplication::GetWindowEventHandler()
    {
        return windowEventHandler;
    }

    EventBus& WindowsApplication::GetEventBus()
    {
        return eventBus;
    }

    void WindowsApplication::Stop()
    {
        isRunning = false;
    }

    HINSTANCE WindowsApplication::GetHInstance()
    {
        return hinstance;
    }

    bool WindowsApplication::IsRunning()
    {
        return isRunning;
    }

    void WindowsApplication::SetRunning(const bool is)
    {
        isRunning = is;
    }

    void WindowsApplication::AddMessageHandler(WindowsMessageHandler& handler)
    {
        handlers.push_front(std::shared_ptr<WindowsMessageHandler>(&handler));
    }

    void WindowsApplication::RemoveMessageHandler(WindowsMessageHandler& handler)
    {
        handlers.remove(std::shared_ptr<WindowsMessageHandler>(&handler));
    }

    SharedRef<Window> WindowsApplication::CreateApplicationWindow(WindowDefinition definition)
    {
        auto window = std::make_shared<WindowsWindow>(*this, definition);
        windows.push_front(window);
        return window;
    }

    Int CALLBACK WindowsApplication::ProcessMessage(HWND hwnd, UInt msg, WPARAM wParam, LPARAM lParam)
    {

        for (const auto& element: handlers)
        {
            (*element)(hwnd, msg, wParam, lParam);
        }

        switch (msg)
        {
            case WM_CLOSE:
            {
                NP_INFO(WindowsWindow, "Main Windows window is close.");
                DestroyWindow(hwnd);
                break;
            }
            case WM_DESTROY:
            {
                PostQuitMessage(0);
                break;
            }
            case WM_KEYDOWN:
            case WM_SYSKEYUP:
            case WM_KEYUP:
            case WM_LBUTTONDBLCLK:
            case WM_LBUTTONDOWN:
            case WM_MBUTTONDBLCLK:
            case WM_MBUTTONDOWN:
            case WM_RBUTTONDBLCLK:
            case WM_RBUTTONDOWN:
            case WM_XBUTTONDBLCLK:
            case WM_XBUTTONDOWN:
            case WM_XBUTTONUP:
            case WM_LBUTTONUP:
            case WM_MBUTTONUP:
            case WM_RBUTTONUP:
            {
                break;
            }
            case WM_NCMOUSEMOVE:
            case WM_MOUSEMOVE:
            {
                Int x = GET_X_LPARAM(lParam);
                Int y = GET_Y_LPARAM(lParam);
                MouseMoveEvent e(x, y, x, y);
                windowEventHandler.EmitOnMouseMove(eventBus, e);
                break;
            }
            case WM_MOUSEWHEEL:
            {
                Int delta = GET_WHEEL_DELTA_WPARAM(wParam);
                Int x = GET_X_LPARAM(lParam);
                Int y = GET_Y_LPARAM(lParam);
                MouseWheelEvent e(delta, y, x);
                windowEventHandler.EmitOnMouseWheel(eventBus, e);
                break;
            }
            case WM_QUIT:
            {
                isRunning = false;
                break;
            }
            default:
                return DefWindowProc(hwnd, msg, wParam, lParam);
        }
        return 0;
    }

    LRESULT WndProcImpl(HWND hwnd, UInt msg, WPARAM wParam, LPARAM lParam)
    {
        return WindowsApplication::WindowsApp->ProcessMessage(hwnd, msg, wParam, lParam);
    }

    LRESULT CALLBACK WindowsApplication::WndProc(HWND hwnd, UInt msg, WPARAM wParam, LPARAM lParam)
    {
        return WndProcImpl(hwnd, msg, wParam, lParam);
    }

    WindowsMessagingDefinition::WindowsMessagingDefinition(
        const SharedRef<WindowsWindow> &InNativeWindow, 
        HWND InHWnd, 
        UInt InMessage, 
        WPARAM InWParam, 
        LPARAM InLParam
    ) 
        : NativeWindow(InNativeWindow)
        , HWnd(InHWnd)
        , WParam(InWParam) 
        , LParam(InLParam)
    { }

}
