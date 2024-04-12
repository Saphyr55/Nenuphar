#include "Nenuphar/ApplicationCore/Windows/WindowsApplication.hpp"
#include "Nenuphar/ApplicationCore/Windows/WindowsWindow.hpp"

#include <ranges>

namespace Nenuphar
{

    thread_local WindowsWindowRegistry WindowsApplication::WindowsWindowRegistry = { };

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
        WNDCLASSEX wcex;
        wcex.cbSize         = sizeof(WNDCLASSEX);
        wcex.style          = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
        wcex.lpfnWndProc    = &ProcessMessage;
        wcex.cbClsExtra     = 0;
        wcex.cbWndExtra     = 0;
        wcex.hInstance      = hinstance;
        wcex.hIcon          = LoadIcon(hinstance, IDI_APPLICATION);
        wcex.hIconSm        = LoadIcon(hinstance, IDI_APPLICATION);
        wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
        wcex.hbrBackground  = reinterpret_cast<HBRUSH>(COLOR_WINDOW + 1);
        wcex.lpszMenuName   = nullptr;
        wcex.lpszClassName  = ApplicationClassName;

        classID = RegisterClassEx(&wcex);
        if (!classID)
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
            ApplicationClassName,
            hinstance
        );
    }

}
