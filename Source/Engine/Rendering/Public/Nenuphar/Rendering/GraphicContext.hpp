#pragma once

#include "Nenuphar/Common/Type/Type.hpp"

namespace Nenuphar
{

    class Window;
    enum class RenderAPI;

    class GraphicContext
    {
    public:
        static UniquePtr<GraphicContext> Create(RenderAPI renderAPI, SharedRef<Window> window);

        virtual void Current() const = 0;

        virtual void SwapBuffers() const = 0;

        virtual ~GraphicContext() = default;

    };

}