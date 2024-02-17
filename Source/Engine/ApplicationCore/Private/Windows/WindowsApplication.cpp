#include "Dramatic/ApplicationCore/Windows/WindowsApplication.hpp"

#include "Dramatic/ApplicationCore/Windows/WindowsWindow.hpp"
#include "Dramatic/Common/Logger/Logger.hpp"

namespace Dramatic
{

    SharedRef<WindowsApplication> WindowsApplication::WindowsApp;

    WindowsMessagingDefinition::WindowsMessagingDefinition(const SharedRef<WindowsWindow> &InNativeWindow,
            const HWND InHWnd, const UInt32 InMessage, const WPARAM InWParam, const LPARAM InLParam): NativeWindow( InNativeWindow )
        , HWnd( InHWnd )
        , Message( InMessage )
        , WParam( InWParam )
        , LParam( InLParam )
    { }

    WindowsApplication::WindowsApplication(HINSTANCE hinstance)
        : hinstance(hinstance)
        , handlers({ })
    {

        WindowsApp = SharedRef<WindowsApplication>(this);

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
            case WM_NCMOUSEMOVE:
            case WM_MOUSEMOVE:
            case WM_MOUSEWHEEL:
                break;
            case WM_QUIT:
            {
                DRL_INFO(WindowsWindow, "Windows window is close.");
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


} // namespace Dramatic
