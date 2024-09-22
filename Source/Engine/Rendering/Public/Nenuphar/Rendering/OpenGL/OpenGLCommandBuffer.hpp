#pragma once

#include "Nenuphar/Common/Type/Type.hpp"
#include "Nenuphar/Rendering/CommandBuffer.hpp"
#include "Nenuphar/Rendering/OpenGL/OpenGLTexture.hpp"
#include <variant>

namespace Nenuphar 
{       

    struct OpenGLViewportCommand
    {
        Viewport Viewport;
    };

    struct OpenGLClearColorCommand
    {
        Vector4f Color;
    };

    struct OpenGLClearCommand
    {
    };

    struct OpenGLDrawIndexedCommand
    {
        UInt IndexCount;
    };

    struct OpenGLBindTextureCommand
    {
        SharedRef<OpenGLTexture> Texture;
        UInt Slot;
    };

    using RenderCommandTypes = std::variant<
        OpenGLViewportCommand,
        OpenGLClearCommand,
        OpenGLClearColorCommand,
        OpenGLDrawIndexedCommand,
        OpenGLBindTextureCommand>;


    class OpenGLCommandBuffer : public CommandBuffer
    {    
    public:
        virtual void Clear() override;

        virtual void ClearColor(const Vector4f& color) override;

        virtual void SetViewport(const Viewport& viewport)override;

        virtual void BindVertexBuffer(SharedRef<RenderBuffer> buffer) override;

        virtual void BindIndexBuffer(SharedRef<RenderBuffer> buffer) override;

        virtual void BindTexture(SharedRef<Texture> texture, UInt slot) override;
        
        virtual void DrawIndexed(UInt indexCount) override;

        virtual void Execute() override;

        void Execute(const OpenGLViewportCommand& command);
        void Execute(const OpenGLClearCommand& command);
        void Execute(const OpenGLClearColorCommand& command);
        void Execute(const OpenGLDrawIndexedCommand& command);

        void Record(RenderCommandTypes command);

    private:
        std::vector<RenderCommandTypes> m_commands;
    };
}