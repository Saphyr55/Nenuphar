#include "Genesis/Transform.hpp"
#include "Nenuphar/Math/Matrix4.hpp"
#include "Nenuphar/Math/Quaternion.hpp"

Matrix4f Transform::Tranformation(const Matrix4f& mat,
                                  const Transform& transform)
{
    auto model = Matrix4f::Translate(mat, transform.Translation);
    model = Matrix4f::Scale(model, transform.Scale);
    // TODO: Add the rotation quaternion as a default neutral element such that M x Q_m = M
    // model = model * Quaternion::ToMat4f(transform.Rotation);
    return model;
}

Matrix4f Transform::Tranformation(const Transform& transform)
{
    return Tranformation(Matrix4f::Identity(), transform);
}
