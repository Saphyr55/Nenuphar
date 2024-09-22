#pragma once

#include "Nenuphar/Rendering/Uniform.hpp"

#include <string>
#include <unordered_map>

namespace Nenuphar 
{

    class UniformRegistry
    {
    public:
        /**
        * @brief 
        * 
        * @tparam TUniformValueType 
        * @param name 
        * @param value 
        * @return UniformRegistry& 
        */
        template<CUniformValueType TUniformValueType>
        UniformRegistry& Register(std::string_view name, TUniformValueType value);

        /**
         * @brief Get the Standard object
         * 
         * @param name 
         * @return StandardUniform& 
         */
        StandardUniform& GetStandard(std::string_view name);

        /**
         * @brief 
         * 
         * @tparam TUniformValueType 
         * @param name 
         * @return Uniform<TUniformValueType> 
         */
        template<CUniformValueType TUniformValueType>
        Uniform<TUniformValueType> Get(std::string_view name);

        /**
         * @brief 
         * 
         * @return SharedRef<Shader> 
         */
        SharedRef<Shader> Owner();
    
    public:
        /**
         * @brief Construct a new Uniform Registry object
         * 
         * @param program 
         */
        explicit UniformRegistry(SharedRef<Shader> program);

    private:
        SharedRef<Shader> m_owner;
        std::unordered_map<std::string, StandardUniform> m_registry;
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