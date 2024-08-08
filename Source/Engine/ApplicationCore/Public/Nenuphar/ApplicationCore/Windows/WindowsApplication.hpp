#pragma once

#include "Nenuphar/Common/Type/Type.hpp"
#include "Nenuphar/Core/Windows.hpp"
#include "Nenuphar/ApplicationCore/PlatformApplication.hpp"

namespace Nenuphar
{

    class WindowsWindow;

    using WindowsWindowRegistry = std::unordered_map<HWND, WindowsWindow*>;

    class WindowsApplication final : public PlatformApplication
    {
        friend WindowsWindow;

    public:
        static const TCHAR ApplicationClassName[];

        HINSTANCE GetHInstance() const;

        void Initialize();

        void Destroy() const override;

        inline ApplicationId Id() const override { return classID; }

        static LRESULT CALLBACK ProcessMessage(HWND hwnd, UInt msg, WPARAM wParam, LPARAM lParam);

        explicit WindowsApplication(HINSTANCE hinstance = GetModuleHandle(nullptr));

        ~WindowsApplication() override;

    private:
        ApplicationId classID;
        HINSTANCE hinstance{};
        static thread_local WindowsWindowRegistry WindowsWindowRegistry;
    };


}
