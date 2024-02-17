#pragma once

#include "WindowsApplication.hpp"
#include "Nenuphar/ApplicationCore/Window.hpp"
#include "Nenuphar/ApplicationCore/WindowDefinition.hpp"
#include "Nenuphar/Core/Windows.hpp"

namespace Nenuphar
{

    class WindowsWindow final : public Window
    {

    public:

        static const char ApplicationWindowClassName[];

        void PoolEvent() const override;

        void Initialize();

        bool IsWindowMaximized() const override;

        bool IsWindowMinimized() const override;

        bool IsVisible() const override;

        void *GetOSWindowHandle() const override;

        void Hide() override;

        void Show() override;

        void Restore() override;

        void Maximaze() override;

        void Destroy() override;

        void ReshapeWindow(Int width, Int height) override;

        void SetTitle(StringView title) override;

        explicit WindowsWindow(WindowsApplication&, WindowDefinition);

        ~WindowsWindow() override;

    private:

        const WindowDefinition Definition;
        WindowsApplication& WindowsApplication;

        HWND Hwnd;

    };

}
