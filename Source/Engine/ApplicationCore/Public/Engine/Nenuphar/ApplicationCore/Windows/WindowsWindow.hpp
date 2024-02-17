#pragma once

#include "WindowsApplication.hpp"
#include "Dramatic/ApplicationCore/Window.hpp"
#include "Dramatic/ApplicationCore/WindowDefinition.hpp"
#include "Dramatic/Core/Windows.hpp"

namespace Dramatic
{

    class WindowsWindow final : public Window
    {

    public:

        static const TCHAR ApplicationWindowClassName[];

        void PoolEvent() const override;

        void Initialize();

        bool IsMaximized() const override;

        bool IsMinimized() const override;

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

        static LRESULT WinProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

    private:

        const WindowDefinition Definition;
        WindowsApplication& WindowsApplication;

        HWND Hwnd;

    };

}
