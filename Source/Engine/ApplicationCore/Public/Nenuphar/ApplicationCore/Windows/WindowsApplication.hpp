#pragma once

#include "Nenuphar/Core/Windows.hpp"
#include <winuser.h>

#if NP_PLATFORM_WINDOWS

#include "Nenuphar/ApplicationCore/PlatformApplication.hpp"
#include "Nenuphar/Common/Type/Type.hpp"

#include <vector>

namespace Nenuphar
{

    class WindowsWindow;

    using WindowsWindowRegistry = std::vector<SharedRef<WindowsWindow>>;

    SharedRef<WindowsWindow> FindWindowByHWND(WindowsWindowRegistry registry, HWND hwnd);

    struct WindowsMessage
    {
    public:
        WeakPtr<WindowsWindow> Window;

        HWND HWnd;
        UInt Message;
        WPARAM WParam;
        LPARAM LParam;

    public:
        WindowsMessage(SharedRef<WindowsWindow> window,
                       HWND hwnd,
                       UInt msg,
                       WPARAM wParam,
                       LPARAM lParam)
            : Window(window)
            , HWnd(hwnd)
            , Message(msg)
            , WParam(wParam)
            , LParam(lParam)
        {
        }
        ~WindowsMessage() = default;
    };

    class WindowsMessageHandler
    {
    public:
        virtual bool ProcessMessage(HWND hwnd, UInt msg, WPARAM wParam, LPARAM lParam, Int& result) = 0;
    };

    /**
     * @brief 
     * 
     */
    class WindowsApplication : public PlatformApplication
    {
        friend WindowsWindow;

    public:
        static const TCHAR ApplicationClassName[];

        HINSTANCE GetHInstance() const;

    public:
        virtual Bool Initialize() override;

        virtual Double GetAbsoluteTime() const override;

        virtual void Destroy() override;

        void AddMessageHandler(WindowsMessageHandler& handler);

        void RemoveMessageHandler(WindowsMessageHandler& handler);

        void DeferMessage(SharedRef<WindowsWindow> window, HWND hwnd, UInt msg, WPARAM wParam, LPARAM lParam);

        LRESULT ProcessMessage(HWND hwnd, UInt msg, WPARAM wParam, LPARAM lParam);

    protected:
        friend LRESULT WindowsApplicationWndProc(HWND hwnd, UInt msg, WPARAM wParam, LPARAM lParam);

        static LRESULT CALLBACK WndProc(HWND hwnd, UInt msg, WPARAM wParam, LPARAM lParam);

    public:
        explicit WindowsApplication(HINSTANCE hinstance);
        ~WindowsApplication() override;

    private:
        std::vector<WindowsMessage> m_defferedWindowsMessage;
        std::vector<WindowsMessageHandler*> m_messageHandlers;
        WindowsWindowRegistry m_registry;

        UInt16 m_classID;
        HINSTANCE m_hinstance{};
    };


}// namespace Nenuphar

#endif