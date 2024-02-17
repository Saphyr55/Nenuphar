#pragma once

#include <forward_list>
#include <functional>

#include "Dramatic/ApplicationCore/Application.hpp"
#include "Dramatic/Common/Type/Type.hpp"
#include "Dramatic/Core/Windows.hpp"

namespace Dramatic
{

    class WindowsWindow;


    using WindowsMessageHandler = std::function<Bool(HWND, UInt, WPARAM, LPARAM)>;


    struct WindowsMessagingDefinition
    {

        WindowsMessagingDefinition(const SharedRef<WindowsWindow>& InNativeWindow,
                                   HWND InHWnd,
                                   UInt InMessage,
                                   WPARAM InWParam,
                                   LPARAM InLParam);


        WeakPtr<WindowsWindow> NativeWindow;

        HWND HWnd;
        UInt Message;
        WPARAM WParam;
        LPARAM LParam;
    };


    class WindowsApplication final : public Application
    {
    public:
        HINSTANCE GetHInstance();

        bool IsRunning() override;

        void SetRunning(bool is) override;

        void AddMessageHandler(WindowsMessageHandler& handler);

        void RemoveMessageHandler(WindowsMessageHandler& handler);

        SharedRef<Window> CreateApplicationWindow(WindowDefinition definition) override;

        Int ProcessMessage(HWND hwnd, UInt msg, WPARAM wParam, LPARAM lParam);

        friend LRESULT WndProcImpl(HWND hwnd, UInt msg, WPARAM wParam, LPARAM lParam);

        static LRESULT CALLBACK WndProc(HWND hwnd, UInt msg, WPARAM wParam, LPARAM lParam);

        explicit WindowsApplication(HINSTANCE hinstance = GetModuleHandle(nullptr));

    private:
        static SharedRef<WindowsApplication> WindowsApp;

        HINSTANCE hinstance;

        Bool isRunning;

        std::forward_list<SharedRef<WindowsWindow>> windows;
        std::forward_list<SharedRef<WindowsMessageHandler>> handlers;
    };

} // namespace Dramatic
