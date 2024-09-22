#include "Nenuphar/Rendering/OpenGL/OpenGLCommandBuffer.hpp"
#include "Nenuphar/Common/Type/Type.hpp"
#include "Nenuphar/Rendering/OpenGL/OpenGL.hpp"
#include "Nenuphar/Rendering/OpenGL/OpenGLBuffer.hpp"
#include "Nenuphar/Rendering/OpenGL/OpenGLDebugger.hpp"
#include "Nenuphar/Rendering/OpenGL/OpenGLTexture.hpp"
#include "glad/glad.h"
#include <memory>
#include <variant>

namespace Nenuphar
{

    void OpenGLCommandBuffer::Record(RenderCommandTypes command)
    {
        m_commands.push_back(command);
    }

    void OpenGLCommandBuffer::Clear()
    {
        Record([] {
        });
    }

    void OpenGLCommandBuffer::ClearColor(const Vector4f& color)
    {
        Record([=] {
        });
    }

    void OpenGLCommandBuffer::SetViewport(const Viewport& viewport)
    {
        OpenGLViewportCommand command;
        command.Viewport = viewport;
        Record(command);
    }

    void OpenGLCommandBuffer::BindVertexBuffer(SharedRef<RenderBuffer> buffer)
    {
    }

    void OpenGLCommandBuffer::BindIndexBuffer(SharedRef<RenderBuffer> buffer)
    {
    }

    void OpenGLCommandBuffer::BindTexture(SharedRef<Texture> texture, UInt slot)
    {
        OpenGLBindTextureCommand command;
        command.Texture = std::reinterpret_pointer_cast<OpenGLTexture>(texture);
        command.Slot = slot;
        Record(command);
    }

    void OpenGLCommandBuffer::DrawIndexed(UInt indexCount)
    {
        OpenGLDrawIndexedCommand command;
        command.IndexCount = indexCount;
        Record(command);
    }

    void OpenGLCommandBuffer::Execute(const OpenGLViewportCommand& command)
    {
        NP_GL_CHECK_CALL(glViewport(command.Viewport.X,
                                    command.Viewport.Y,
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
        NP_GL_CHECK_CALL(glDrawElements(GL_TRIANGLES, command.IndexCount, GL_UNSIGNED_INT, nullptr));
    }

    void OpenGLCommandBuffer::Execute()
    {
        for (const auto& command: m_commands)
        {
            std::visit([&](const auto& c) {
                Execute(c);
            },
                       command);
        }
    }

}// namespace Nenuphar