#pragma once

namespace Nenuphar
{
    
    class PipelineState
    {
    public:
        virtual void Execute() = 0;
    };

}// namespace Nenuphar