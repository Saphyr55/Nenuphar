#include "Nenuphar/ApplicationCore/Clock.hpp"
#include "Nenuphar/ApplicationCore/PlatformApplication.hpp"
#include "Nenuphar/Core/Debug.hpp"

namespace Nenuphar 
{
    
    void ClockStart(SharedRef<PlatformApplication> platformApplication, Clock& clock)
    {
        NCHECK(platformApplication)
        Double absoluteTime = platformApplication->GetAbsoluteTime();
        clock.StartTime = absoluteTime;
        clock.Elapsed = 0;
    }

    void ClockTick(SharedRef<PlatformApplication> platformApplication, Clock& clock)
    {
        NCHECK(platformApplication)
        if (clock.StartTime != 0)
        {
            Double absoluteTime = platformApplication->GetAbsoluteTime();
            clock.Elapsed = absoluteTime - clock.StartTime;
        }
    }
    
    void ClockStop(Clock& clock)
    {
        clock.StartTime = 0;
    }

}