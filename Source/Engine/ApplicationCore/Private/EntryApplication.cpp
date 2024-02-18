#include "Nenuphar/ApplicationCore/EntryApplication.hpp"

#include "Nenuphar/Core/Engine.hpp"

namespace Nenuphar
{

    EntryApplication::EntryApplication(SharedRef<Application> application)
        : inner(application)
    {
    }

    EntryApplication::~EntryApplication() = default;

    void EntryApplication::Initialize()
    {
    }

    void EntryApplication::Update(float deltaTime)
    {
    }

    void EntryApplication::Destroy() const
    {
        inner->Destroy();
    }

    void EntryApplication::Stop()
    {
        inner->Stop();
    }

    EventBus& EntryApplication::GetEventBus()
    {
        return inner->GetEventBus();
    }

    bool EntryApplication::IsRunning() const
    {
        return inner->IsRunning();
    }

    void EntryApplication::SetRunning(bool enable)
    {
        inner->SetRunning(enable);
    }


}
