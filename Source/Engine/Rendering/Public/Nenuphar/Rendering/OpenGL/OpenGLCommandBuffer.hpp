#pragma once

#include "Nenuphar/Common/Type/Type.hpp"
#include "Nenuphar/Rendering/CommandBuffer.hpp"
#include "Nenuphar/Rendering/OpenGL/OpenGLTexture.hpp"
#include "Nenuphar/Rendering/OpenGL/OpenGLVertexArray.hpp"
#include "Nenuphar/Rendering/UniformRegistry.hpp"
#include <variant>

namespace Nenuphar
{

    struct OpenGLRenderCommand
    {
        RenderCommand Command;
    };

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
        SharedRef<OpenGLVertexArray> VAO;
        // SharedRef<UniformRegistry> Bindings;
        UInt IndexCount;
    };

    struct OpenGLBindTextureCommand
    {
        SharedRef<OpenGLTexture> Texture;
        UInt Slot;
    };

    using OpenGLRenderCommandTypes = std::variant<
            OpenGLRenderCommand,
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

        virtual void SetViewport(const Viewport& viewport) override;

        virtual void BindTexture(SharedRef<Texture> texture, UInt slot) override;
        
        virtual void DrawIndexed(SharedRef<RenderHandle> handle, UInt indexCount) override;

        virtual void Record(const RenderCommand& command) override;

        virtual void Execute() override;

        void Execute(const OpenGLRenderCommand& command);
        void Execute(const OpenGLViewportCommand& command);
        void Execute(const OpenGLClearCommand& command);
        void Execute(const OpenGLClearColorCommand& command);
        void Execute(const OpenGLDrawIndexedCommand& command);
        void Execute(const OpenGLBindTextureCommand& command);

        void Record(OpenGLRenderCommandTypes command);

    private:
        std::vector<OpenGLRenderCommandTypes> m_commands;
    };
}// namespace Nenuphar