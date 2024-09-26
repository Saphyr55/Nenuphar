#pragma once

#include "Nenuphar/Core/Windows.hpp"

#if NP_PLATFORM_WINDOWS

#include "Nenuphar/ApplicationCore/Window.hpp"
#include "Nenuphar/ApplicationCore/Windows/WindowsApplication.hpp"

namespace Nenuphar
{
    
    class WindowsWindow : public Window
    {
        friend WindowsApplication;

    public:

        virtual WindowID GetID() const override;

        virtual const WindowDefinition& GetWindowDefinition() const override;
        
        virtual bool IsWindowMaximized() const override;

        virtual bool IsWindowMinimized() const override;

        virtual bool IsVisible() const override;

        virtual void* GetOSWindowHandle() const override;

        virtual void Hide() override;

        virtual void Show() override;

        virtual void Restore() override;

        virtual void Maximize() override;

        virtual void Destroy() override;

        virtual void ReshapeWindow(Int width, Int height) override;

        virtual void SetTitle(StringView title) override;

        HWND GetHWND();

        WindowsWindow(WindowsApplication& application, const WindowDefinition& definition);

        virtual ~WindowsWindow() override;

    private:
        bool IsValid();

        void InitializeWindowHandle();

    private:
        WindowDefinition m_definition;
        WindowsApplication& m_windowsApplication;
        HWND m_hwnd;
        WindowID ID;
        static WindowID LastID;
    };

}

#endif