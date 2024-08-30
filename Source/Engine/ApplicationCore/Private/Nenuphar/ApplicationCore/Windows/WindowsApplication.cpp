#include "Nenuphar/ApplicationCore/Windows/WindowsApplication.hpp"
#include "Nenuphar/ApplicationCore/Windows/WindowsWindow.hpp"

#if NP_PLATFORM_WINDOWS

namespace Nenuphar
{

    thread_local WindowsWindowRegistry WindowsApplication::WindowsWindowRegistry = {};

    const TCHAR WindowsApplication::ApplicationClassName[] = TEXT("NenupharApplication");

    WindowsApplication::WindowsApplication(HINSTANCE hinstance)
        : hinstance(hinstance)
        , classID(0)
    {
        Initialize();
    }

    WindowsApplication::~WindowsApplication()
    {
        Destroy();
    }

    HINSTANCE WindowsApplication::GetHInstance() const
    {
        return hinstance;
    }

    LRESULT CALLBACK WindowsApplication::ProcessMessage(HWND hwnd, UInt msg, WPARAM wParam, LPARAM lParam)
    {

        if (!WindowsWindowRegistry.contains(hwnd))
        {
            return DefWindowProc(hwnd, msg, wParam, lParam);
        }

        WindowsWindow* window = WindowsWindowRegistry[hwnd];

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
        windowClassEX.hInstance = hinstance;
        windowClassEX.hIcon = LoadIcon(hinstance, IDI_APPLICATION);
        windowClassEX.hIconSm = LoadIcon(hinstance, IDI_APPLICATION);
        windowClassEX.hCursor = LoadCursor(nullptr, IDC_ARROW);
        windowClassEX.hbrBackground = reinterpret_cast<HBRUSH>(COLOR_WINDOW + 1);
        windowClassEX.lpszMenuName = nullptr;
        windowClassEX.lpszClassName = ApplicationClassName;

        classID = RegisterClassEx(&windowClassEX);
        if (!classID)
        {
            NP_ERROR(WindowsWindow, "Call to RegisterClassEx failed!");
            return;
        }

        NP_INFO(WindowsWindow, "Windows Application Instance has been registered.");
        NP_INFO(WindowsWindow, "Nenuphar Application was started with a windows instance.");
    }

    void WindowsApplication::Destroy() const
    {
        UnregisterClass(
                ApplicationClassName,
                hinstance);
    }

}// namespace Nenuphar

#endif