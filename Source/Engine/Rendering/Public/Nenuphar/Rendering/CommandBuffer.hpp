#pragma once

#include "Nenuphar/Common/Type/Type.hpp"
#include "Nenuphar/Math/Vector4.hpp"
#include "Nenuphar/Rendering/Texture.hpp"


namespace Nenuphar
{

    struct Viewport
    {
        UInt X = 0;
        UInt Y = 0;
        UInt Width = 0;
        UInt Height = 0;
    };

    using RenderCommand = std::function<void()>;

    class CommandBuffer
    {
    public:
        virtual void Record(const RenderCommand& command) = 0;

        virtual void Clear() = 0;

        virtual void ClearColor(const Vector4f& color) = 0;
        
        virtual void SetViewport(const Viewport& viewport) = 0;

        virtual void BindTexture(SharedRef<Texture> texture, UInt slot) = 0;
        
        virtual void DrawIndexed(SharedRef<RenderHandle> handle, UInt indexCount) = 0;
        
        virtual void Execute() = 0;
    };

}// namespace Nenuphar