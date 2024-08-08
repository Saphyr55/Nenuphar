#pragma once

#include "Nenuphar/Core/Core.hpp"
#include "Nenuphar/Math/Vector4.hpp"
#include "Nenuphar/Rendering/Texture.hpp"

namespace Nenuphar
{

    enum class GraphicsAPI
    {
        None = 0,
        OpenGL = 1
    };

    class RenderSystem
    {
    public:
        static RenderSystem& Instance(GraphicsAPI type = GraphicsAPI::OpenGL);

        virtual void Enable() const = 0;

        virtual void Clear(const Vector4f& color) const = 0;
    };



}