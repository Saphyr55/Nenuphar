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
        while (!m_commandQueue.empty()) 
        {
            SharedRef<CommandBuffer> commandBuffer = m_commandQueue.front();
            commandBuffer->Execute();
            m_commandQueue.pop();
        }
    }

}