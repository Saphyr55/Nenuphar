#pragma once

#include "Nenuphar/Common/Type/Type.hpp"

namespace Nenuphar
{
    using ShaderId = UInt32;
    using ShaderProgramId = UInt32;

    class Shader
    {
    public:

        virtual void Use() const = 0;

        virtual ShaderProgramId Id() const = 0;

        virtual ~Shader() = default;
    };
    
}