#pragma once

#include <forward_list>
#include <functional>
#include <set>

#include "Nenuphar/ApplicationCore/Application.hpp"
#include "Nenuphar/Common/Type/Type.hpp"
#include "Nenuphar/Core/Windows.hpp"
#include "Nenuphar/EventSystem.hpp"

namespace Nenuphar
{

    class WindowsWindow;
    
    using WindowRegistry = std::unordered_map<WindowID, SharedRef<Window>>;

    class WindowsApplication final : public Application
    {
    public:
        friend WindowsWindow;

        bool IsRunning() const override;

        EventBus& GetEventBus() override;

        void Stop() override;

        void SetRunning(bool is) override;

        Int ProcessMessage(HWND hwnd, UInt msg, WPARAM wParam, LPARAM lParam);

        HINSTANCE GetHInstance() const;

        friend LRESULT WndProcImpl(HWND hwnd, UInt msg, WPARAM wParam, LPARAM lParam);

        static LRESULT CALLBACK WndProc(HWND hwnd, UInt msg, WPARAM wParam, LPARAM lParam);

        void Initialize() const;

        void Destroy() const override;

        explicit WindowsApplication(HINSTANCE hinstance = GetModuleHandle(nullptr));

        ~WindowsApplication() override;

        WindowRegistry& GetRegistry() { return windowRegistry; }

        void Emit(HWND handle, std::function<void(SharedRef<Window>)> func);

    private:
        static WindowsApplication* WindowsApp;
        HINSTANCE hinstance{};
        Bool isRunning{};
        EventBus eventBus;
        WindowRegistry windowRegistry;
    };

}
