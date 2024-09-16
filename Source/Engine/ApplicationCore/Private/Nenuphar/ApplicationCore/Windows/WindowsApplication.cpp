#include "Nenuphar/ApplicationCore/Windows/WindowsApplication.hpp"
#include "Nenuphar/ApplicationCore/Windows/WindowsWindow.hpp"
#include <profileapi.h>
#include <winnt.h>

#if NP_PLATFORM_WINDOWS

namespace Nenuphar
{
    using WindowsWindowRegistry = std::unordered_map<HWND, WindowsWindow*>;

    static Double GClockFrequency;
    static LARGE_INTEGER GStartTime;

    static WindowsWindowRegistry GWindowsWindowRegistry;

    const TCHAR WindowsApplication::ApplicationClassName[] = TEXT("NenupharApplication");
    
    void RegisterWindowsWindow(HWND handle, WindowsWindow* windowsWindow)
    {
        GWindowsWindowRegistry.emplace(handle, windowsWindow);
    }

    SharedRef<PlatformApplication> PlatformAppCreate()
    {
        return MakeSharedRef<WindowsApplication>(GetModuleHandle(nullptr));
    }

    WindowsApplication::WindowsApplication(HINSTANCE hinstance)
        : m_hinstance(hinstance)
        , m_classID(0)
    {
        Initialize();
    }

    WindowsApplication::~WindowsApplication()
    {
        Destroy();
    }

    HINSTANCE WindowsApplication::GetHInstance() const
    {
        return m_hinstance;
    }

    LRESULT CALLBACK WindowsApplication::ProcessMessage(HWND hwnd, UInt msg, WPARAM wParam, LPARAM lParam)
    {

        if (!GWindowsWindowRegistry.contains(hwnd))
        {
            return DefWindowProc(hwnd, msg, wParam, lParam);
        }

        WindowsWindow* window = GWindowsWindowRegistry[hwnd];

        MSG message{};
        message.hwnd = hwnd;
        message.lParam = lParam;
        message.wParam = wParam;
        message.message = msg;
        message.time = 0;

        return window->ProcessEvent(message);
    }

    void WindowsApplication::Initialize()
    {
        WNDCLASSEX windowClassEX;
        windowClassEX.cbSize = sizeof(WNDCLASSEX);
        windowClassEX.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
        windowClassEX.lpfnWndProc = &ProcessMessage;
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
            NP_ERROR(WindowsWindow, "Call to RegisterClassEx failed!");
            return;
        }

        NP_INFO(WindowsWindow, "Windows Application Instance has been registered.");
        NP_INFO(WindowsWindow, "Nenuphar Application was started with a windows instance.");

        LARGE_INTEGER frequency;
        QueryPerformanceFrequency(&frequency);
        GClockFrequency = 1.0 / (Double) frequency.QuadPart;
        QueryPerformanceCounter(&GStartTime);
    }

    Double WindowsApplication::GetAbsoluteTime() const
    {
        LARGE_INTEGER now;
        QueryPerformanceCounter(&now);
        
        return (Double) now.QuadPart * GClockFrequency;
    }

    void WindowsApplication::Destroy()
    {
        UnregisterClass(ApplicationClassName, m_hinstance);
    }

}// namespace Nenuphar

#endif