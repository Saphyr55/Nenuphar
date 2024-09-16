#pragma once

#include "Nenuphar/Common/Common.hpp"

namespace Nenuphar
{

    class Application;
    class WindowEventHandler;
    class WindowSignals;

    using WindowID = UInt16;


    struct WindowDefinition
    {
        String Title;
        Float Width;
        Float Height;
    };


    enum class WindowMode : Int
    {
        Fullscreen,

        WindowedFullscreen,

        Windowed,
    };


    class Window
    {
    public:
        virtual const WindowDefinition& GetWindowDefinition() const = 0;

        virtual const WindowSignals& GetWindowSignals() const = 0;

        virtual WindowID GetID() const = 0;

        virtual Bool IsWindowMaximized() const = 0;

        virtual Bool IsWindowMinimized() const = 0;

        virtual Bool IsVisible() const = 0;

        virtual void* GetOSWindowHandle() const = 0;

        virtual void PoolEvent() const = 0;

        virtual void Hide() = 0;

        virtual void Show() = 0;

        virtual void Restore() = 0;

        virtual void Maximize() = 0;

        virtual void Destroy() = 0;

        virtual void ReshapeWindow(Int width, Int height) = 0;

        virtual void SetTitle(StringView title) = 0;

        virtual ~Window() = default;

    };

}