#pragma once

#include "Nenuphar/Rendering/Uniform.hpp"
#include "Uniform.hpp"

#include <string>
#include <string_view>

namespace Nenuphar 
{

    class UniformRegistry
    {
    public:
        template<CUniformValueType TUniformValueType>
        UniformRegistry& Register(std::string_view name, TUniformValueType value);

        StandardUniform& GetStandard(std::string_view name);

        template<CUniformValueType TUniformValueType>
        Uniform<TUniformValueType> Get(std::string_view name);


        SharedRef<Shader> Owner();
    
    public:
        explicit UniformRegistry(SharedRef<Shader> program);

    private:
        SharedRef<Shader> m_owner;
        std::map<std::string, StandardUniform> m_registry;
    };

    template<CUniformValueType TUniformValueType>
    Uniform<TUniformValueType> UniformRegistry::Get(std::string_view name)
    {   
        return std::get<Uniform<TUniformValueType>>(GetStandard(name));
    }

    template<CUniformValueType TUniformValueType>
    UniformRegistry& UniformRegistry::Register(std::string_view name, TUniformValueType value)
    {   
        m_registry.insert(std::make_pair(name.data(), Uniform<decltype(value)>(m_owner, name, value)));
        return *this;
    }
    
}