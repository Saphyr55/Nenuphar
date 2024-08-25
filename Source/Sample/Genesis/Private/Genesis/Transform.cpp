#include "Genesis/Transform.hpp"
#include "Nenuphar/Math/Matrix4.hpp"

namespace gn
{


    Matrix4f Transform::Tranformation(const Transform& transform)
    {
        return Matrix4f::Translate(Matrix4f::Identity(), transform.Translation);
    }

    
}