#pragma once

#include "Nenuphar/Common/Type/Type.hpp"


namespace Nenuphar
{
    class AppDelegate;
    class Application;
    class PlatformApplication;    

    /**
     * @brief 
     * 
     * @param appDelegate 
     * @return SharedRef<Application> 
     */
    SharedRef<Application> AppCreate(SharedRef<AppDelegate> appDelegate);

    /**
     * @brief 
     * 
     */
    void AppMakeCurrent(SharedRef<Application> application);

    /**
     * @brief 
     * 
     * @return SharedRef<Application> 
     */
    SharedRef<Application> AppGetCurrent();

    /**
     * @brief 
     * 
     */
    void AppStopCurrent();

    /**
     * @brief 
     * 
     */
    void AppSuspendCurrent();


    /**
     * @brief 
     * 
     */
    struct AppContext
    {
    };


    /**
     * @brief 
     * 
     */
    class AppDelegate
    {
    public:
        /**
         * @brief Provide an application context to the principal application. 
         * It configure the application.
         * 
         * @return AppContext* The application context to supply.
         */
        virtual AppContext* ProvideAppContext() = 0;
    
    public:
        /**
         * @brief 
         * 
         */
        virtual Bool OnInitialize() { return true; };
        
        /**
         * @brief 
         * 
         * @param deltaTime 
         */
        virtual void OnTick(Double deltaTime) { };

        /**
         * @brief 
         * 
         */
        virtual void OnSuspend() { }

        /**
         * @brief 
         * 
         */
        virtual void OnClose() { };

    };


    /**
     * @brief 
     * 
     */
    class Application
    {
    public:
        virtual Bool Initialize() = 0;

        virtual void Start() = 0;

        virtual void Tick(Double deltaTime) = 0;

        virtual void Close() = 0;

    public:
        virtual void Stop() = 0;

        virtual void Resume() = 0;

        virtual void Suspend() = 0;

        virtual Bool IsRunning() const = 0;

        virtual Bool IsSuspended() const = 0;

        virtual Double GetLastTime() const = 0;

    public:
        virtual ~Application() = default;
    };


}// namespace Nenuphar
