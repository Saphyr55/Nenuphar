#pragma once

#include "Nenuphar/Common/Type/Type.hpp"
#include "Nenuphar/Math/Vector4.hpp"
#include "Nenuphar/Rendering/Renderer.hpp"

namespace Nenuphar
{

    class RenderService
    {
    public:
        
        static SharedRef<RenderService> Instance();
                
        virtual SharedRef<Renderer> GetRenderer() = 0;

        virtual void Enable() const = 0;

        virtual void Clear(const Vector4f& color) const = 0;

        virtual ~RenderService() = default;
    };



}