#pragma once

namespace Nenuphar
{

    class RunnableEngineInterface
    {
    public:
        virtual ~RunnableEngineInterface() = default;

        virtual void Setup() = 0;

        virtual void Update(float deltaTime) = 0;

        virtual void Stop() = 0;

        virtual bool IsRunning() = 0;
    };

}
