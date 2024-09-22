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
        
    }

    void WindowsApplication::Destroy()
    {
        UnregisterClass(ApplicationClassName, m_hinstance);
    }

}// namespace Nenuphar

#endif