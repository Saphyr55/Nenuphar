#include "Nenuphar/Rendering/OpenGL/OpenGLCommandBuffer.hpp"
#include "Nenuphar/Common/Type/Type.hpp"
#include "Nenuphar/Core/Debug.hpp"
#include "Nenuphar/Rendering/CommandBuffer.hpp"
#include "Nenuphar/Rendering/OpenGL/OpenGL.hpp"
#include "Nenuphar/Rendering/OpenGL/OpenGLDebugger.hpp"
#include "Nenuphar/Rendering/OpenGL/OpenGLTexture.hpp"
#include "Nenuphar/Rendering/OpenGL/OpenGLVertexArray.hpp"

#include <memory>
#include <variant>

namespace Nenuphar
{

    void OpenGLCommandBuffer::Record(const RenderCommand& renderCommand)
    {
        OpenGLRenderCommand command;
        command.Command = renderCommand;
        Record(std::move(command));
    }

    void OpenGLCommandBuffer::Record(OpenGLRenderCommandTypes command)
    {
        m_commands.push_back(std::move(command));
    }

    void OpenGLCommandBuffer::Clear()
    {
        OpenGLClearCommand command;
        Record(std::move(command));
    }

    void OpenGLCommandBuffer::ClearColor(const Vector4f& color)
    {
        OpenGLClearColorCommand command;
        command.Color = color;
        Record(std::move(command));
    }

    void OpenGLCommandBuffer::SetViewport(const Viewport& viewport)
    {
        OpenGLViewportCommand command;
        command.Viewport = viewport;
        Record(std::move(command));
    }

    void OpenGLCommandBuffer::BindTexture(SharedRef<Texture> texture, UInt slot)
    {
        OpenGLBindTextureCommand command;
        command.Texture = std::reinterpret_pointer_cast<OpenGLTexture>(texture);
        command.Slot = slot;
        NCHECK(command.Texture);
        Record(std::move(command));
    }

    void OpenGLCommandBuffer::DrawIndexed(SharedRef<RenderHandle> handle, UInt indexCount)
    {
        OpenGLDrawIndexedCommand command;
        command.IndexCount = indexCount;
        command.VAO = std::reinterpret_pointer_cast<OpenGLVertexArray>(handle);
        Record(std::move(command));
    }

    void OpenGLCommandBuffer::Execute(const OpenGLRenderCommand& command)
    {
        command.Command();
    }

    void OpenGLCommandBuffer::Execute(const OpenGLViewportCommand& command)
    {
        NP_GL_CHECK_CALL(glViewport((Int)command.Viewport.X,
                                    (Int)command.Viewport.Y,
                                    command.Viewport.Width,
                                    command.Viewport.Height));
    }

    void OpenGLCommandBuffer::Execute(const OpenGLClearCommand&)
    {
        NP_GL_CHECK_CALL(glClear(OpenGLBufferMask::ColorBuffer | OpenGLBufferMask::DepthBuffer));
    }

    void OpenGLCommandBuffer::Execute(const OpenGLClearColorCommand& command)
    {
        NP_GL_CHECK_CALL(glClearColor(command.Color.x, command.Color.y, command.Color.z, command.Color.w));
    }

    void OpenGLCommandBuffer::Execute(const OpenGLDrawIndexedCommand& command)
    {
        NCHECK(command.VAO)
        command.VAO->Bind();
        NP_GL_CHECK_CALL(glDrawElements(GL_TRIANGLES, command.IndexCount, GL_UNSIGNED_INT, nullptr));
    }

    void OpenGLCommandBuffer::Execute(const OpenGLBindTextureCommand& command)
    {
        NCHECK(command.Texture);
        command.Texture->BindTextureUnit(command.Slot);
    }

    void OpenGLCommandBuffer::Execute()
    {
        auto runCommand = [this](const auto& c) {
            Execute(c);
        };

        for (const auto& command: m_commands)
        {
            std::visit(runCommand, command);
        }
    }

}// namespace Nenuphar