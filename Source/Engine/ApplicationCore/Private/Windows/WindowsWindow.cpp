#include <utility>

#include <fmt/format.h>

#include "Nenuphar/ApplicationCore/Windows/WindowsWindow.hpp"
#include "Nenuphar/ApplicationCore/Windows/WindowsApplication.hpp"
#include "Nenuphar/Core.hpp"
#include "Nenuphar/Common/Instanciate.hpp"

namespace Nenuphar
{

    const TCHAR WindowsWindow::ApplicationWindowClassName[] = TEXT("NenupharWindow");
    WindowID WindowsWindow::LastID = 0;

    Void WindowsWindow::PoolEvent() const
    {
        MSG msg;
        while (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    WindowID WindowsWindow::GetID() const
    {
        return ID;
    }

    const WindowEventHandler& WindowsWindow::GetWindowEventHandler() const
    {
        return windowEventHandler;
    }

    HWND WindowsWindow::Initialize()
    {
        const char* Title = definition.Title.c_str();

        hwnd = CreateWindowEx
        (
            WS_EX_OVERLAPPEDWINDOW,
            ApplicationWindowClassName,
            Title,
            WS_OVERLAPPEDWINDOW,
            CW_USEDEFAULT,
            CW_USEDEFAULT,
            static_cast<Int>(definition.Width),
            static_cast<Int>(definition.Height),
            nullptr,
            nullptr,
            windowsApplication.GetHInstance(),
            nullptr
        );

        if (!hwnd)
        {
            NP_ERROR(WindowsWindow, "Call to CreateWindow failed, enable to create windows window.");
            return hwnd;
        }

        return hwnd;
    }

    bool WindowsWindow::IsWindowMaximized() const
    {
        return false;
    }

    bool WindowsWindow::IsWindowMinimized() const
    {
        return false;
    }

    bool WindowsWindow::IsVisible() const
    {
        return false;
    }

    void* WindowsWindow::GetOSWindowHandle() const
    {
        return hwnd;
    }

    void WindowsWindow::Hide()
    {
        ShowWindow(hwnd, SW_HIDE);
    }

    void WindowsWindow::Show()
    {
        ShowWindow(hwnd, SW_NORMAL);
    }

    void WindowsWindow::Restore()
    {
        ShowWindow(hwnd, SW_RESTORE);
    }

    void WindowsWindow::Maximaze()
    {
        ShowWindow(hwnd, SW_SHOWMAXIMIZED);
    }

    void WindowsWindow::Destroy()
    {
        DestroyWindow(hwnd);
    }

    void WindowsWindow::ReshapeWindow(Int width, Int height)
    {
    }

    void WindowsWindow::SetTitle(StringView title)
    {
    }

    WindowsWindow::WindowsWindow(WindowsApplication& application_,
                                 WindowDefinition definition_)
        : definition(std::move(definition_))
        , windowsApplication(application_)
        , hwnd(Initialize())
        , ID(++LastID)
        , windowEventHandler(ID)
    {

        if (hwnd)
        {

            NP_INFO(WindowsWindow, "Windows window was created sucessfully.");
            NP_DEBUG(WindowsWindow, "Windows window configuration : ");
            NP_DEBUG(WindowsWindow, "      ID = {}", ID);
            NP_DEBUG(WindowsWindow, "      HWND = {}", fmt::ptr(hwnd));
            NP_DEBUG(WindowsWindow, "      Width = {}", definition.Width);
            NP_DEBUG(WindowsWindow, "      Height = {}", definition.Height);
            NP_DEBUG(WindowsWindow, "      Title = {}", definition.Title);

            windowsApplication.GetRegistry().insert({ ID, SharedRef<WindowInterface>(this) });
        }

    }

    WindowsWindow::~WindowsWindow() = default;

}
