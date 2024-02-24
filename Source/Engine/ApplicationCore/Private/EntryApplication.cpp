#include "Nenuphar/ApplicationCore/EntryApplication.hpp"

#include "Nenuphar/Core/Engine.hpp"

namespace Nenuphar
{

    EntryApplication::EntryApplication(Application& application)
        : inner(application)
        , isRunning(false)
    {
    }

    EntryApplication::~EntryApplication() = default;


    void EntryApplication::Update(Float deltaTime)
    {
    }

    void EntryApplication::Setup()
    {
        isRunning = true;
    }

    void EntryApplication::Stop()
    {
        isRunning = false;
    }

    bool EntryApplication::IsRunning()
    {
        return isRunning;
    }

    void EntryApplication::Destroy() const
    {
        inner.Destroy();
    }

    EventBus& EntryApplication::GetEventBus()
    {
        return inner.GetEventBus();
    }


}
