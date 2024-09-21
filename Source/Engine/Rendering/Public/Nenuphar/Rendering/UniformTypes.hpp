#pragma once

#include "Nenuphar/Common/Type/Type.hpp"
#include "Nenuphar/Math/Math.hpp"

#include <variant>

namespace Nenuphar
{
    using UniformLocation = Int;

    using UniformValueType = std::variant<
            Matrix4f,
            Vector2f,
            Vector3f,
            Vector4f,
            Float,
            UInt,
            Int,
            Bool>;

    using UniformUpdater = std::function<void(UniformLocation, UniformValueType)>;

    template<typename T>
    concept CUniformValueType =
            std::is_same_v<T, Matrix4f> or
            std::is_same_v<T, Vector2f> or
            std::is_same_v<T, Vector3f> or
            std::is_same_v<T, Vector4f> or
            std::is_same_v<T, Float> or
            std::is_same_v<T, UInt> or
            std::is_same_v<T, Int> or
            std::is_same_v<T, Bool>;

}// namespace Nenuphar