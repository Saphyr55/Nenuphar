#include "Nenuphar/ApplicationCore/Windows/WindowsApplication.hpp"

#if NP_PLATFORM_WINDOWS

#include "Nenuphar/ApplicationCore/Windows/WindowsWindow.hpp"
#include "Nenuphar/Common/Type/Type.hpp"
#include "Nenuphar/InputSystem/Button.hpp"

#include <mmiscapi.h>
#include <profileapi.h>
#include <windef.h>
#include <winnt.h>

namespace Nenuphar
{
    static Double GClockFrequency;
    static LARGE_INTEGER GStartTime;
    const TCHAR WindowsApplication::ApplicationClassName[] = TEXT("NenupharApplication");
    static Float GLastMouseX = 0;
    static Float GLastMouseY = 0;
    WindowsApplication* GWindowsApplication = nullptr;

    SharedRef<PlatformApplication> PlatformAppGet()
    {
        static SharedRef<WindowsApplication> WindowsApplication_ = [&] {
            auto windowsApp = MakeSharedRef<WindowsApplication>(GetModuleHandle(nullptr));
            GWindowsApplication = windowsApp.get();
            return windowsApp;
        }();

        return WindowsApplication_;
    }

    SharedRef<WindowsWindow> FindWindowByHWND(WindowsWindowRegistry registry, HWND hwnd)
    {
        for (auto& window: registry)
        {
            if (window->GetHWND() == hwnd)
            {
                return window;
            }
        }
        return nullptr;
    }

    WindowsApplication::WindowsApplication(HINSTANCE hinstance)
        : m_hinstance(hinstance)
        , m_classID(0)
        , m_applicationMessageHandler(MakeSharedRef<ApplicationMessageHandler>())
    {
    }

    WindowsApplication::~WindowsApplication()
    {
    }
    
    void WindowsApplication::SetApplicationMessageHandler(SharedRef<ApplicationMessageHandler> handler) 
    {
        m_applicationMessageHandler = handler;
    }

    HINSTANCE WindowsApplication::GetHInstance() const
    {
        return m_hinstance;
    }

    LRESULT WindowsApplication::ProcessMessage(HWND hwnd, UInt msg, WPARAM wParam, LPARAM lParam)
    {
        SharedRef<WindowsWindow> window = FindWindowByHWND(m_registry, hwnd);

        Int externalResult = 0;

        for (WindowsMessageHandler*& handler: m_messageHandlers)
        {
            Int result;
            if (handler->ProcessMessage(hwnd, msg, wParam, lParam, result))
            {
                externalResult = result;
            }
        }

        switch (msg)
        {
            case WM_ERASEBKGND: {
                return 1;
            }
            case WM_SIZE: {
                UInt width = LOWORD(lParam);
                UInt height = HIWORD(lParam);
                m_applicationMessageHandler->OnWindowResize(window, width, height);
                break;
            }
            case WM_PAINT: {
                break;
            }
            case WM_SYSKEYUP:
            case WM_KEYUP:
            case WM_SYSKEYDOWN:
            case WM_KEYDOWN: {

                Input::Key key = static_cast<Input::Key>(wParam);

                bool down = (msg == WM_KEYDOWN || msg == WM_SYSKEYDOWN);
                bool repeat = (HIWORD(lParam) & KF_REPEAT) == KF_REPEAT;

                if (down)
                {
                    m_applicationMessageHandler->OnKeyDown(key);
                }
                else
                {
                    m_applicationMessageHandler->OnKeyUp(key);
                }

                break;
            }
            case WM_LBUTTONUP:
            case WM_MBUTTONUP:
            case WM_RBUTTONUP:
            case WM_LBUTTONDOWN:
            case WM_MBUTTONDOWN:
            case WM_RBUTTONDOWN: {

                Input::Button button;
                bool down =
                        msg == WM_LBUTTONDOWN ||
                        msg == WM_RBUTTONDOWN ||
                        msg == WM_MBUTTONDOWN;

                switch (msg)
                {
                    case WM_LBUTTONDOWN:
                    case WM_LBUTTONUP:
                        button = Input::Button::Left;
                        break;
                    case WM_MBUTTONUP:
                    case WM_MBUTTONDOWN:
                        button = Input::Button::Middle;
                        break;
                    case WM_RBUTTONUP:
                    case WM_RBUTTONDOWN:
                        button = Input::Button::Right;
                        break;
                    default:
                        break;
                }

                if (down)
                {
                    m_applicationMessageHandler->OnButtonDown(button);
                }
                else
                {
                    m_applicationMessageHandler->OnButtonUp(button);
                }

                break;
            }
            case WM_XBUTTONDOWN:
            case WM_XBUTTONUP: {

                Input::Button button = GET_XBUTTON_WPARAM(wParam) == XBUTTON1
                                               ? Input::Button::XButton1
                                               : Input::Button::XButton2;

                if (msg == WM_XBUTTONDOWN)
                {
                    m_applicationMessageHandler->OnButtonDown(button);
                }
                else
                {
                    m_applicationMessageHandler->OnButtonUp(button);
                }

                break;
            }
            case WM_NCMOUSEMOVE:
            case WM_MOUSEMOVE: {
                float x = GET_X_LPARAM(lParam);
                float y = GET_Y_LPARAM(lParam);
                float relX = x - GLastMouseX;
                float relY = y - GLastMouseY;
                GLastMouseX = x;
                GLastMouseY = y;
                m_applicationMessageHandler->OnMouseMove(relX, relY, x, y);
                break;
            }
            case WM_MOUSEWHEEL: {
                Float delta = GET_WHEEL_DELTA_WPARAM(wParam);
                m_applicationMessageHandler->OnMouseWheel(delta);
                break;
            }
            case WM_SHOWWINDOW: {
                if (!::GetLayeredWindowAttributes(hwnd, NULL, NULL, NULL))
                {
                    ::SetLayeredWindowAttributes(hwnd, 0, 0, LWA_ALPHA);
                    ::DefWindowProc(hwnd, WM_ERASEBKGND, (WPARAM)GetDC(hwnd), lParam);
                    ::SetLayeredWindowAttributes(hwnd, 0, 255, LWA_ALPHA);
                    ::AnimateWindow(hwnd, 200, AW_ACTIVATE | AW_BLEND);
                    return 0;
                }
                break;
            }
            case WM_CLOSE: {
                NP_INFO(WindowsWindow, "The window ID={}, HWND={} closed.", window->GetID(), fmt::ptr(hwnd));
                m_applicationMessageHandler->OnWindowClose(window);
                return externalResult;
            }
            case WM_DESTROY: {
                PostQuitMessage(externalResult);
                return externalResult;
            }
            default:
                break;
        }

        return ::DefWindowProc(hwnd, msg, wParam, lParam);
    }

    LRESULT WindowsApplicationWndProc(HWND hwnd, UInt msg, WPARAM wParam, LPARAM lParam)
    {
        return GWindowsApplication->ProcessMessage(hwnd, msg, wParam, lParam);
    }

    LRESULT CALLBACK WindowsApplication::WndProc(HWND hwnd, UInt msg, WPARAM wParam, LPARAM lParam)
    {
        return WindowsApplicationWndProc(hwnd, msg, wParam, lParam);
    }

    void WindowsApplication::PumpMessages()
    {
        MSG msg;
        while (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    SharedRef<Window> WindowsApplication::MakeWindow(const WindowDefinition& definition)
    {
        SharedRef<WindowsWindow> windowsWindow = MakeSharedRef<WindowsWindow>(*this, definition);
        m_registry.push_back(windowsWindow);
        return windowsWindow;
    }

    Bool WindowsApplication::Initialize()
    {
        WNDCLASSEX windowClassEX;
        windowClassEX.cbSize = sizeof(WNDCLASSEX);
        windowClassEX.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
        windowClassEX.lpfnWndProc = &WndProc;
        windowClassEX.cbClsExtra = 0;
        windowClassEX.cbWndExtra = 0;
        windowClassEX.hInstance = m_hinstance;
        windowClassEX.hIcon = LoadIcon(m_hinstance, IDI_APPLICATION);
        windowClassEX.hIconSm = LoadIcon(m_hinstance, IDI_APPLICATION);
        windowClassEX.hCursor = LoadCursor(nullptr, IDC_ARROW);
        windowClassEX.hbrBackground = reinterpret_cast<HBRUSH>(COLOR_WINDOW + 1);
        windowClassEX.lpszMenuName = nullptr;
        windowClassEX.lpszClassName = ApplicationClassName;

        m_classID = RegisterClassEx(&windowClassEX);
        if (!m_classID)
        {
            NP_CRITICAL(WindowsWindow, "Call to RegisterClassEx failed!");
            return false;
        }

        NP_INFO(WindowsWindow, "Windows Application Instance has been registered.");
        NP_INFO(WindowsWindow, "Nenuphar Application was started with a windows instance.");

        LARGE_INTEGER frequency;
        QueryPerformanceFrequency(&frequency);
        GClockFrequency = 1.0 / (Double)frequency.QuadPart;
        QueryPerformanceCounter(&GStartTime);

        return true;
    }

    Double WindowsApplication::GetAbsoluteTime() const
    {
        LARGE_INTEGER now;
        QueryPerformanceCounter(&now);

        return (Double)now.QuadPart * GClockFrequency;
    }

    void WindowsApplication::AddMessageHandler(WindowsMessageHandler& handler)
    {
        m_messageHandlers.push_back(&handler);
    }

    void WindowsApplication::RemoveMessageHandler(WindowsMessageHandler& handler)
    {
        m_messageHandlers.remove(&handler);
    }

    void WindowsApplication::DeferMessage(SharedRef<WindowsWindow> window, HWND hwnd, UInt msg, WPARAM wParam, LPARAM lParam)
    {
    }

    void WindowsApplication::Destroy()
    {
        UnregisterClass(ApplicationClassName, m_hinstance);
    }

}// namespace Nenuphar

#endif