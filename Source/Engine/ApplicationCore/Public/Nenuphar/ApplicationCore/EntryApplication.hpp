#pragma once
#include "Application.hpp"
#include "PlatformApplication.hpp"
#include "Nenuphar/Core/RunnableEngineInterface.hpp"

namespace Nenuphar
{

    class EntryApplication : public ApplicationInterface 
    {

    public:
        virtual void Update(Float deltaTime);

        virtual void Setup();

        virtual void Stop();

        virtual bool IsRunning();

    public:
        void Destroy() const override;

        EventBus& GetEventBus() override;

    public:
        explicit EntryApplication(Application& application = PlatformApplication::GetPlatformApplication());

        virtual ~EntryApplication() override;

    private:
        Application& inner;
        Bool isRunning;
    };


}
