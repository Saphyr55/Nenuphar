#pragma once
#include "Application.hpp"

namespace Nenuphar
{

    class EntryApplication : public Application
    {
    public:

        EntryApplication(SharedRef<Application> application);

        ~EntryApplication() override;

        virtual void Initialize();

        virtual void Update(Float deltaTime);

        void Destroy() const override;

        void Stop() override;

        EventBus& GetEventBus() override;

        bool IsRunning() const override;

        void SetRunning(bool enable) override;

    private:
        SharedRef<Application> inner;

    };


}
