#pragma once

#include "Nenuphar/Common/Type/Type.hpp"
#include "Nenuphar/Math/Matrix4.hpp"
#include "Nenuphar/Math/Vector2.hpp"
#include "Nenuphar/Math/Vector3.hpp"
#include "Nenuphar/Math/Vector4.hpp"
#include "Nenuphar/Rendering/Shader.hpp"

#include <variant>


namespace Nenuphar
{

    template<CUniformValueType TUniformValueType>
    class Uniform
    {
    public:
        void Update() const;
        void UpdateValue(const TUniformValueType& value);
        [[nodiscard]] const TUniformValueType& GetValue() const;
        [[nodiscard]] UniformLocation GetLocation() const;

    public:
        Uniform(SharedRef<Shader> shader,
                std::string_view name,
                TUniformValueType value);

    private:
        UniformUpdater m_updater;
        std::string m_name;
        UniformLocation m_location;
        SharedRef<Shader> m_owner;
        TUniformValueType m_value;
    };

    using StandardUniform = std::variant<
            Uniform<Int>,
            Uniform<Bool>,
            Uniform<UInt>,
            Uniform<Float>,
            Uniform<Vector2f>,
            Uniform<Vector3f>,
            Uniform<Vector4f>,
            Uniform<Matrix4f>>;

    template<CUniformValueType TUniform>
    void Uniform<TUniform>::UpdateValue(const TUniform& value_)
    {
        m_value = value_;
        Update();
    }

    template<CUniformValueType TUniform>
    void Uniform<TUniform>::Update() const
    {
        m_owner->Use();
        m_updater(m_location, m_value);
    }

    template<CUniformValueType TUniform>
    const TUniform& Uniform<TUniform>::GetValue() const
    {
        return m_value;
    }

    template<CUniformValueType TUniform>
    UniformLocation Uniform<TUniform>::GetLocation() const
    {
        return m_location;
    }

    template<CUniformValueType TUniform>
    Uniform<TUniform>::Uniform(SharedRef<Shader> shader, StringView name, TUniform value)
        : m_owner(shader)
        , m_updater(shader->GetUniformUpdater())
        , m_name(name)
        , m_value(value)
    {
        m_location = m_owner->GetUniformLocation(name);
        Update();
    }


}// namespace Nenuphar