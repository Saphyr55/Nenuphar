#pragma once

#include "Nenuphar/Common/Type/Type.hpp"


namespace Nenuphar
{

    class PlatformApplication;

    /**
     * @brief 
     * 
     */
    struct Clock
    {
        Double StartTime;
        Double Elapsed;
    };

    /**
     * @brief 
     * 
     * @param platformApplication 
     * @param clock 
     */
    void ClockStart(SharedRef<PlatformApplication> platformApplication, Clock& clock);

    /**
     * @brief 
     * 
     * @param platformApplication 
     * @param clock 
     */
    void ClockTick(SharedRef<PlatformApplication> platformApplication, Clock& clock);

    /**
     * @brief 
     * 
     * @param clock 
     */
    void ClockStop(Clock& clock);

}