#pragma once

#include "Nenuphar/ApplicationCore/WindowBase.hpp"
#include "Nenuphar/ApplicationCore/Windows/WindowsApplication.hpp"
#include "Nenuphar/ApplicationCore/WindowDefinition.hpp"
#include "Nenuphar/Core/Windows.hpp"
#include "Nenuphar/EventSystem/EventSystem.hpp"


namespace Nenuphar
{

    class WindowsWindow : public WindowBase
    {
        friend WindowsApplication;
    public:

        WindowID GetID() const override;

        const WindowDefinition& GetWindowDefinition() const override;

        const WindowSignals& GetWindowSignals() const override;

        bool IsWindowMaximized() const override;

        bool IsWindowMinimized() const override;

        bool IsVisible() const override;

        void* GetOSWindowHandle() const override;

        void PoolEvent() const override;

        void Hide() override;

        void Show() override;

        void Restore() override;

        void Maximize() override;

        void Destroy() override;

        void ReshapeWindow(Int width, Int height) override;

        void SetTitle(StringView title) override;

        WindowsWindow(WindowsApplication& inApplication, WindowDefinition inDefinition);

        ~WindowsWindow() override = default;

    private:
        HWND Initialize();
        Int ProcessEvent(MSG msg);

    private:
        WindowSignals m_windowSignals;
        WindowDefinition m_definition;
        WindowsApplication& windowsApplication;
        HWND hwnd;
        WindowID ID;
        static WindowID LastID;
    };

}
