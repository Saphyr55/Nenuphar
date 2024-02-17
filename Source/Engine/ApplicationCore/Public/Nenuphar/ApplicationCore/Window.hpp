#pragma once

#include "Nenuphar/Common.hpp"

namespace Nenuphar
{

    enum class WindowMode : Int
    {
        Fullscreen,

        WindowedFullscreen,

        Windowed,
    };

    class Window
    {
    public:

        virtual void PoolEvent() const;

        virtual bool IsMaximized() const;

        virtual bool IsMinimized() const;

        virtual bool IsVisible() const;

        virtual void* GetOSWindowHandle() const;

        virtual void Hide();

        virtual void Show();

        virtual void Restore();

        virtual void Maximaze();

        virtual void Destroy();

        virtual void ReshapeWindow(Int width, Int height);

        virtual void SetTitle(StringView title);

        virtual ~Window() = default;

    };

}