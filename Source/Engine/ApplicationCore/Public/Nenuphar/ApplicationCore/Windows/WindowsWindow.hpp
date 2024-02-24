#pragma once

#include "Nenuphar/ApplicationCore/WindowBase.hpp"
#include "Nenuphar/ApplicationCore/Windows/WindowsApplication.hpp"
#include "Nenuphar/ApplicationCore/WindowDefinition.hpp"
#include "Nenuphar/Core/Windows.hpp"

namespace Nenuphar
{

    class WindowsWindow final : public WindowBase
    {

    public:

        static const TCHAR ApplicationWindowClassName[];

        Void PoolEvent() const override;

        WindowID GetID() const override;

        const WindowEventHandler& GetWindowEventHandler() const override;

        Bool IsWindowMaximized() const override;

        Bool IsWindowMinimized() const override;

        Bool IsVisible() const override;

        Void* GetOSWindowHandle() const override;

        Void Hide() override;

        Void Show() override;

        Void Restore() override;

        Void Maximaze() override;

        Void Destroy() override;

        Void ReshapeWindow(Int width, Int height) override;

        Void SetTitle(StringView title) override;

        HWND Initialize();

        WindowsWindow(WindowsApplication& application, 
                      WindowDefinition definition);

        ~WindowsWindow() override;

    private:
        WindowDefinition definition;
        WindowsApplication& windowsApplication;
        HWND hwnd;
        WindowID ID;
        WindowEventHandler windowEventHandler;
        static WindowID LastID;
    };

}