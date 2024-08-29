#pragma once

#include <map>
#include <type_traits>
#include <variant>

#include "Nenuphar/Common/Type/Type.hpp"
#include "Nenuphar/Math/Vector2.hpp"
#include "Nenuphar/Math/Vector3.hpp"
#include "Nenuphar/Math/Vector4.hpp"
#include "Nenuphar/Rendering/OpenGL/OpenGL.hpp"
#include "Nenuphar/Rendering/OpenGL/OpenGLDebugger.hpp"
#include "Nenuphar/Rendering/OpenGL/OpenGLShader.hpp"


namespace Nenuphar
{

    using UniformLocation = UInt;


    template<typename T>
    concept IsUniformValue =
            std::is_same_v<T, Matrix4f> or
            std::is_same_v<T, Vector2f> or
            std::is_same_v<T, Vector3f> or
            std::is_same_v<T, Vector4f> or
            std::is_same_v<T, Float> or
            std::is_same_v<T, UInt> or
            std::is_same_v<T, Int> or
            std::is_same_v<T, Bool>;

    template<IsUniformValue T>
    class Uniform
    {

    public:
        void Update() const;
        void UpdateValue(const T& value) const;
        [[nodiscard]] const T& GetValue() const;
        [[nodiscard]] UniformLocation GetLocation() const;

    public:
        Uniform(OpenGLShader& shader, std::string_view name, T value);

    private:
        std::string m_name;
        UniformLocation m_location;
        OpenGLShader& m_owner;
        mutable T m_value;
    };

    using UniformBool = Uniform<Bool>;
    using UniformInt = Uniform<Int>;
    using UniformSampler2D = Uniform<UInt>;
    using UniformU32 = Uniform<UInt>;
    using UniformFloat = Uniform<Float>;
    using UniformVec4f = Uniform<Vector4f>;
    using UniformVec3f = Uniform<Vector3f>;
    using UniformVec2f = Uniform<Vector2f>;
    using UniformMat4f = Uniform<Matrix4f>;


    using IUniform = std::variant<
            Uniform<Int>,
            Uniform<Bool>,
            Uniform<UInt>,
            Uniform<Float>,
            Uniform<Vector2f>,
            Uniform<Vector3f>,
            Uniform<Vector4f>,
            Uniform<Matrix4f>>;


    class UniformRegistry
    {
    public:
        UniformRegistry& Register(StringView name, IsUniformValue auto value);

        template<IsUniformValue V>
        Uniform<V>& Get(StringView name);

        template<IsUniformValue V>
        UniformRegistry& Handle(StringView name, std::function<void(Uniform<V>&)> handle);

        inline OpenGLShader& Owner()
        {
            return m_owner;
        }

        UniformRegistry(OpenGLShader& s)
            : m_owner(s)
        {
        }

    private:
        OpenGLShader& m_owner;
        std::map<String, IUniform> m_registry;
    };


    template<IsUniformValue T>
    void Uniform<T>::UpdateValue(const T& value_) const
    {
        m_value = value_;
        Update();
    }

    template<IsUniformValue T>
    void Uniform<T>::Update() const
    {
        m_owner.Use();
        SetUniform(m_location, m_value);
    }

    template<IsUniformValue T>
    const T& Uniform<T>::GetValue() const
    {
        return m_value;
    }

    template<IsUniformValue T>
    UniformLocation Uniform<T>::GetLocation() const
    {
        return m_location;
    }

    template<IsUniformValue T>
    Uniform<T>::Uniform(OpenGLShader& shader, StringView name, T value)
        : m_value(value), m_owner(shader), m_name(name)
    {
        m_location = NPOGL_CHECK_RCALL(glGetUniformLocation(m_owner.Id(), name.data()));
        Update();
    }

    UniformRegistry& UniformRegistry::Register(StringView name, IsUniformValue auto value)
    {
        m_registry.insert(std::make_pair(name.data(), Uniform<decltype(value)>(m_owner, name, value)));
        return *this;
    }

    template<IsUniformValue V>
    auto UniformRegistry::Get(StringView name) -> Uniform<V>&
    {
        IUniform& uniform = m_registry.at(name.data());
        return std::get<Uniform<V>>(uniform);
    }

    template<IsUniformValue V>
    UniformRegistry& UniformRegistry::Handle(std::string_view name, std::function<void(Uniform<V>&)> handle)
    {
        Uniform<V> uniform = Get<V>(name);
        handle(uniform);
        return *this;
    }

}// namespace Nenuphar