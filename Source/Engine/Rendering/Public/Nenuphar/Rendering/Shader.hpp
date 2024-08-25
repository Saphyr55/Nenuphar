#pragma once

#include "Nenuphar/Common/Type/Type.hpp"

namespace Nenuphar
{
    using ShaderId = UInt;
    using ShaderProgramId = UInt;

    class Shader
    {
    public:
        virtual void Use() const = 0;

        virtual ShaderProgramId Id() const = 0;

        virtual ~Shader() = default;
    };
    
}