#include "Nenuphar/ApplicationCore/Windows/WindowsApplication.hpp"
#include "Nenuphar/ApplicationCore/Windows/WindowsWindow.hpp"
#include "Nenuphar/Common/Type/Type.hpp"

#include <mmiscapi.h>
#include <profileapi.h>
#include <windef.h>
#include <winnt.h>

#if NP_PLATFORM_WINDOWS

namespace Nenuphar
{
    static Double GClockFrequency;
    static LARGE_INTEGER GStartTime;
    const TCHAR WindowsApplication::ApplicationClassName[] = TEXT("NenupharApplication");

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
    {
    }

    WindowsApplication::~WindowsApplication()
    {
    }

    HINSTANCE WindowsApplication::GetHInstance() const
    {
        return m_hinstance;
    }

    LRESULT WindowsApplication::ProcessMessage(HWND hwnd, UInt msg, WPARAM wParam, LPARAM lParam)
    {
        SharedRef<WindowsWindow> currentWindow = FindWindowByHWND(m_registry, hwnd);

        Int externalResult = 0;

        for (WindowsMessageHandler*& handler : m_messageHandlers)
        {
            Int result;
            if (handler->ProcessMessage(hwnd, msg, wParam, lParam, result))
            {   
                externalResult = result;
            }
        }

        return DefWindowProc(hwnd, msg, wParam, lParam);
    }

    LRESULT WindowsApplicationWndProc(HWND hwnd, UInt msg, WPARAM wParam, LPARAM lParam)
    {
        return GWindowsApplication->ProcessMessage(hwnd, msg, wParam, lParam);
    }

    LRESULT CALLBACK WindowsApplication::WndProc(HWND hwnd, UInt msg, WPARAM wParam, LPARAM lParam)
    {
        return WindowsApplicationWndProc(hwnd, msg, wParam, lParam);
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
        
    }

    void WindowsApplication::RemoveMessageHandler(WindowsMessageHandler& handler)
    {

    }

    void WindowsApplication::DeferMessage(SharedRef<WindowsWindow> window, HWND hwnd, UInt msg, WPARAM wParam, LPARAM lParam)
    {
        switch (msg)
        {
            case WM_SIZE: {
                auto width = Float(LOWORD(lParam));
                auto height = Float(HIWORD(lParam));
                m_definition.Width = width;
                m_definition.Height = height;
                m_windowSignals.EmitOnResize(ResizeEvent(width, height));
                break;
            }
            case WM_PAINT: {
                break;
            }
            case WM_SYSKEYDOWN:
            case WM_KEYDOWN: {
                KeyEvent e(static_cast<Input::Key>(wParam));
                if ((HIWORD(lParam) & KF_REPEAT) != KF_REPEAT)
                {
                    m_windowSignals.EmitOnKeyPressed(e);
                }

                m_windowSignals.EmitOnKeyDown(e);
                break;
            }
            case WM_LBUTTONUP: {
                const auto button = Input::Button::Left;
                const MouseButtonEvent e(button);
                m_windowSignals.EmitOnButtonRelease(e);
                break;
            }
            case WM_MBUTTONUP: {
                const auto button = Input::Button::Middle;
                const MouseButtonEvent e(button);
                m_windowSignals.EmitOnButtonRelease(e);
                break;
            }
            case WM_RBUTTONUP: {
                const auto button = Input::Button::Right;
                const MouseButtonEvent e(button);
                m_windowSignals.EmitOnButtonRelease(e);
                break;
            }
            case WM_LBUTTONDOWN: {
                const auto button = Input::Button::Left;
                const MouseButtonEvent e(button);
                m_windowSignals.EmitOnButtonDown(e);
                break;
            }
            case WM_MBUTTONDOWN: {
                const auto button = Input::Button::Middle;
                const MouseButtonEvent e(button);
                m_windowSignals.EmitOnButtonDown(e);
                break;
            }
            case WM_RBUTTONDOWN: {
                const auto button = Input::Button::Right;
                const MouseButtonEvent e(button);
                m_windowSignals.EmitOnButtonDown(e);
                break;
            }
            case WM_XBUTTONDOWN:
            case WM_XBUTTONUP: {
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
            case WM_KEYUP: {
                const KeyEvent e(static_cast<Input::Key>(wParam));
                m_windowSignals.EmitOnKeyRelease(e);
                break;
            }
            case WM_NCMOUSEMOVE:
            case WM_MOUSEMOVE: {
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
            case WM_MOUSEWHEEL: {
                const Float delta = GET_WHEEL_DELTA_WPARAM(wParam);
                const Float x = GET_X_LPARAM(lParam);
                const Float y = GET_Y_LPARAM(lParam);
                const MouseWheelEvent e(delta, y, x);
                m_windowSignals.EmitOnMouseWheel(e);
                break;
            }
            case WM_CLOSE: {
                CloseEvent closeEvent;
                NP_INFO(WindowsWindow, "The window ID={}, HWND={} closed.", ID, fmt::ptr(hwnd));
                m_windowSignals.EmitOnClose(closeEvent);
                return EXIT_SUCCESS;
            }
            case WM_DESTROY: {
                PostQuitMessage(EXIT_SUCCESS);
                return EXIT_SUCCESS;
            }
            default:
                break;
        }
        
        return 0;
    }

    void WindowsApplication::Destroy()
    {
        UnregisterClass(ApplicationClassName, m_hinstance);
    }

}// namespace Nenuphar

#endif