#pragma once

#include "Nenuphar/ApplicationCore/WindowDefinition.hpp"
#include "Nenuphar/ApplicationCore/Window.hpp"

namespace Nenuphar
{

    class PlatformApplication;

    class WindowBase : public Window
    {
    public:
        static SharedRef<WindowBase> Create(const WindowDefinition& definition);

        virtual const WindowSignals& GetWindowSignals() const override = 0;

        virtual WindowID GetID() const override = 0;

        virtual Bool IsWindowMaximized() const override = 0;

        virtual Bool IsWindowMinimized() const override = 0;

        virtual Bool IsVisible() const override = 0;

        virtual VoidPtr GetOSWindowHandle() const override = 0;

        virtual void PoolEvent() const override = 0;

        virtual void Hide() override = 0;

        virtual void Show() override = 0;

        virtual void Restore() override = 0;

        virtual void Maximize() override = 0;

        virtual void Destroy() override = 0;

        virtual void ReshapeWindow(Int width, Int height) override = 0;

        virtual void SetTitle(StringView title) override = 0;

        ~WindowBase() override = default;
    };

}

