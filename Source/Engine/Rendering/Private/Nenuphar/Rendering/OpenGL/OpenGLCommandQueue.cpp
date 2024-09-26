#include "Nenuphar/Rendering/OpenGL/OpenGLCommandQueue.hpp"
#include "Nenuphar/Common/Type/Type.hpp"

namespace Nenuphar
{

    void OpenGLCommandQueue::Submit(SharedRef<CommandBuffer> commandBuffer)
    {
        m_commandQueue.push(commandBuffer);
    }

    void OpenGLCommandQueue::Execute()
    {
        for (SharedRef<CommandBuffer> commandBuffer = m_commandQueue.front(); !m_commandQueue.empty(); m_commandQueue.pop())
        {
            commandBuffer->Execute();
        }
    }

}// namespace Nenuphar