#pragma once 

#include "Nenuphar/Rendering/CommandQueue.hpp"

#include <queue>

namespace Nenuphar 
{
    class OpenGLCommandQueue : public CommandQueue
    {
    public:
        virtual void Submit(SharedRef<CommandBuffer> commandBuffer) override;

        virtual void Execute() override;

    private:
        std::queue<SharedRef<CommandBuffer>> m_commandQueue;
    };

}