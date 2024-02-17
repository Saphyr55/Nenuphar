#include "Nenuphar/ApplicationCore/Windows/WindowsWindow.hpp"
#include "Nenuphar/Core.hpp"

namespace Nenuphar
{

    const TCHAR WindowsWindow::ApplicationWindowClassName[] = TEXT("DramaticWindow");

    void WindowsWindow::PoolEvent() const
    {
        MSG msg;
        while (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    void WindowsWindow::Initialize()
    {

        WNDCLASSEX wcex;
        wcex.cbSize         = sizeof(WNDCLASSEX);
        wcex.style          = CS_HREDRAW | CS_VREDRAW;
        wcex.lpfnWndProc    = WindowsApplication::WndProc;
        wcex.cbClsExtra     = 0;
        wcex.cbWndExtra     = 0;
        wcex.hInstance      = WindowsApplication.GetHInstance();
        wcex.hIcon          = LoadIcon(wcex.hInstance, IDI_APPLICATION);
        wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
        wcex.hbrBackground  = reinterpret_cast<HBRUSH>(COLOR_WINDOW + 1);
        wcex.lpszMenuName   = nullptr;
        wcex.lpszClassName  = ApplicationWindowClassName;
        wcex.hIconSm        = LoadIcon(wcex.hInstance, IDI_APPLICATION);

        if (!RegisterClassEx(&wcex))
        {
            NP_ERROR(WindowsWindow, "Call to RegisterClassEx failed!");
            return;
        }

        NP_INFO(WindowsWindow, "Windows Application Instance has been registed.");
        NP_INFO(WindowsWindow, "Dramatic Application was started with a windows instance.");

        const TCHAR* Title = Definition.Title.c_str();

        Hwnd = CreateWindowEx
        (
            WS_EX_OVERLAPPEDWINDOW,
            ApplicationWindowClassName,
            Title,
            WS_OVERLAPPEDWINDOW,
            static_cast<Int>(Definition.PosX),
            static_cast<Int>(Definition.PosY),
            static_cast<Int>(Definition.Width),
            static_cast<Int>(Definition.Height),
            nullptr,
            nullptr,
            WindowsApplication.GetHInstance(),
            nullptr
        );

        if (!Hwnd)
        {
            NP_ERROR(WindowsWindow, "Call to CreateWindow failed, enable to create windows window.");
            return;
        }

        NP_INFO (WindowsWindow, "Windows window was created sucessfully.");
        NP_DEBUG(WindowsWindow, "Windows window configuration : "        );
        NP_DEBUG(WindowsWindow, "      Width = {}",  Definition.Width    );
        NP_DEBUG(WindowsWindow, "      Height = {}", Definition.Height   );
        NP_DEBUG(WindowsWindow, "      Title = {}",  Definition.Title    );
        NP_DEBUG(WindowsWindow, "      PosX = {}",   Definition.PosX     );
        NP_DEBUG(WindowsWindow, "      PosY = {}",   Definition.PosY     );
    }

    bool WindowsWindow::IsMaximized() const
    {
        return false;
    }

    bool WindowsWindow::IsMinimized() const
    {
        return false;
    }

    bool WindowsWindow::IsVisible() const
    {
        return false;
    }

    void* WindowsWindow::GetOSWindowHandle() const
    {
        return Hwnd;
    }

    void WindowsWindow::Hide()
    {
        ShowWindow(Hwnd, SW_HIDE);
    }

    void WindowsWindow::Show()
    {
        ShowWindow(Hwnd, SW_NORMAL);
    }

    void WindowsWindow::Restore()
    {
        ShowWindow(Hwnd, SW_RESTORE);
    }

    void WindowsWindow::Maximaze()
    {
        ShowWindow(Hwnd, SW_SHOWMAXIMIZED);
    }

    void WindowsWindow::Destroy()
    {
        UnregisterClass
        (
            ApplicationWindowClassName,
            WindowsApplication.GetHInstance()
        );
    }

    void WindowsWindow::ReshapeWindow(Int width, Int height)
    {
    }

    void WindowsWindow::SetTitle(StringView title)
    {
    }

    WindowsWindow::WindowsWindow(class WindowsApplication& application,
                                 WindowDefinition definition)
        : Definition(definition)
        , WindowsApplication(application)
        , Hwnd(nullptr)
    {
        Initialize();
    }

    WindowsWindow::~WindowsWindow()
    {
        Destroy();
    }

} // namespace Dramatic::Windows
