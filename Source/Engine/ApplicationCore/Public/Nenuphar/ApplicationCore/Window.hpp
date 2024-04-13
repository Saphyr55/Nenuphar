#pragma once

#include "WindowDefinition.hpp"
#include "WindowInterface.hpp"
#include "PlatformApplication.hpp"

namespace Nenuphar
{

    class WindowBase;

    class Window : public WindowInterface
    {
    public:

        void PoolEvent() const override;

        const WindowDefinition& GetWindowDefinition() const override;

        const WindowSignals& GetWindowSignals() const override;

        WindowID GetID() const override;

        bool IsWindowMaximized() const override;

        bool IsWindowMinimized() const override;

        bool IsVisible() const override;

        void* GetOSWindowHandle() const override;

        void Hide() override;

        void Show() override;

        void Restore() override;

        void Maximize() override;

        void Destroy() override;

        void ReshapeWindow(int width, int height) override;

        void SetTitle(StringView title) override;

        inline WindowBase& Base() { return *m_base; }

    public:
        Window(
            const WindowDefinition& definition, 
            PlatformApplication& app = PlatformApplication::GetPlatformApplication());

        Window(StringView title, Int width, Int height);

        ~Window() override = default;

    private:
        SharedRef<WindowBase> m_base;
    };
}
