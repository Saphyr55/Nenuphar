#pragma once

#include "Nenuphar/ApplicationCore/Application.hpp"
#include "Nenuphar/Common/Type/Type.hpp"


namespace Nenuphar
{

    class Window;
    class WindowDefinition;
    class PlatformApplication;
    class ApplicationMessageHandler;


    /**
     * @brief 
     * 
     * @return SharedRef<PlatformApplication> 
     */
    SharedRef<PlatformApplication> PlatformAppGet();


    /**
     * @brief 
     * 
     */
    class PlatformApplication
    {
    public:

        /**
         * @brief 
         * 
         */
        virtual bool Initialize() = 0;

        /**
         * @brief
         * 
         */
        virtual void SetApplicationMessageHandler(SharedRef<ApplicationMessageHandler> handler) = 0;

        /**
         * @brief 
         * 
         * @return
         */
        virtual bool PumpMessages() = 0;

        /**
         * @brief Create a new Window.
         * 
         * @return SharedRef<Window> 
         */
        virtual SharedRef<Window> MakeWindow(const WindowDefinition& definition) = 0; 

        /**
         * @brief Get the absolute time.
         * 
         * @return double 
         */
        virtual double GetAbsoluteTime() const = 0;
        
        /**
         * @brief 
         * 
         */
        virtual void Destroy() = 0;
        
        /**
         * @brief Destroy the Platform Application object
         * 
         */
        virtual ~PlatformApplication() = default;
    };
    
}
