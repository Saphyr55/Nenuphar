#pragma once

#include "Nenuphar/ApplicationCore/Application.hpp"
#include "Nenuphar/Common/Type/Type.hpp"


namespace Nenuphar
{

    class PlatformApplication
    {
    public:

        /**
         * @brief 
         * 
         */
        virtual void Initialize() = 0;

        /**
         * @brief Get the absolute time.
         * 
         * @return Double 
         */
        virtual Double GetAbsoluteTime() const = 0;

        /**
         * @brief 
         * 
         */
        virtual void Destroy() = 0;
        
    public:
        virtual ~PlatformApplication() = default;

    };

    SharedRef<PlatformApplication> PlatformAppCreate();

}
