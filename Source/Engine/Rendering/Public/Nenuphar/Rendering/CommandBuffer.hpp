#pragma once

#include "Nenuphar/Common/Type/Type.hpp"
#include "Nenuphar/Math/Vector4.hpp"
#include "Nenuphar/Rendering/Texture.hpp"
#include "RenderBuffer.hpp"


namespace Nenuphar
{

    using RenderCommand = std::function<void()>;

    struct Viewport
    {
        int X;
        int Y;
        int Width;
        int Height;
    };

    class CommandBuffer
    {
    public:
        virtual void Clear() = 0;

        virtual void ClearColor(const Vector4f& color) = 0;
        
        virtual void SetViewport(const Viewport& viewport) = 0;
    
        virtual void BindVertexBuffer(SharedRef<RenderBuffer> buffer) = 0;

        virtual void BindIndexBuffer(SharedRef<RenderBuffer> buffer) = 0;

        virtual void BindTexture(SharedRef<Texture> texture, UInt slot) = 0;

        virtual void DrawIndexed(UInt indexCount) = 0;
        
        virtual void Execute() = 0;
    };

}// namespace Nenuphar