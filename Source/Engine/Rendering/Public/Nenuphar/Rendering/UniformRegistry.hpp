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
         * @param name 
         * @param value 
         * @return UniformRegistry& 
         */
        UniformRegistry& Register(std::string_view name, CUniformValueType auto value);

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
         * @return Uniform<TUniformValueType>&
         */
        template<CUniformValueType TUniformValueType>
        Uniform<TUniformValueType>& Get(std::string_view name);

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
    Uniform<TUniformValueType>& UniformRegistry::Get(std::string_view name)
    {   
        return std::get<Uniform<TUniformValueType>>(GetStandard(name));
    }

    UniformRegistry& UniformRegistry::Register(std::string_view name, CUniformValueType auto value)
    {   
        using ValueType = decltype(value); 
        m_registry.insert(std::make_pair(std::string(name.data()), Uniform<ValueType>(m_owner, name, value)));
        return *this;
    }
    
}