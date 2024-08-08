#pragma once

#include <array>

#include "Nenuphar/Math/CommonMath.hpp"
#include "Nenuphar/Math/Vector3.hpp"

template<Real R>
struct Matrix3
{
    using Mat = Matrix3<R>;
    using Vec = Vector3<R>;

    Mat operator*(Mat m);
    Vec operator*(Vec v);
    Vec& operator[](std::size_t i);
    Vec GetCol(UInt index) const;

    Matrix3() = default;
    Matrix3(R r);
    Matrix3(R m11, R m21, R m31,
            R m12, R m22, R m32,
            R m13, R m23, R m33);
    Matrix3(const Vec& col_1, const Vec& col_2, const Vec& col_3);

    static Matrix3 Identity();
    static std::array<R, 3 * 3> ValueArray(Mat mat);
    static Matrix3 Translate(Mat mat, Vector3<R> vec);
    static Matrix3 Scale(Mat mat, Vector3<R> vec);
    static Matrix3 Rotate(Mat mat, const Real auto& theta, Vector3<R> vec);
    static Matrix3 RotateX(Float theta);
    static Matrix3 RotateY(Float theta);
    static Matrix3 RotateZ(Float theta);

private:
    Vec value[3];
};


using Matrix3f = Matrix3<Float>;
using Matrix3d = Matrix3<Double>;

#include "Nenuphar/Math/Matrix3.inl"