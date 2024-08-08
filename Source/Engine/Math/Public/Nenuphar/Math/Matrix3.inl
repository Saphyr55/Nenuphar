#include "Nenuphar/Math/Matrix3.hpp"

#include <cassert>
#include <cmath>

template<Real R>
Matrix3<R> Matrix3<R>::Identity()
{
    return Matrix3(1);
}

template<Real R>
std::array<R, 3 * 3> Matrix3<R>::ValueArray(Mat mat)
{
    std::array<R, 3 * 3> content;
    for (Int8 i = 0; i < 3; i++)
    {
        for (Int8 j = 0; j < 3; j++)
        {
            content[i * 3 + j] = mat[i][j];
        }
    }
    return content;
}

template<Real R>
Matrix3<R> Matrix3<R>::Translate(Mat mat, Vector3<R> vec)
{
    Mat transformation_mat(1);
    transformation_mat[2] = vec;
    return mat * transformation_mat;
}

template<Real R>
Matrix3<R> Matrix3<R>::Scale(Mat mat, Vector3<R> vec)
{
    return mat * Mat(
                    Vector3<R>(vec.x, 0, 0),
                    Vector3<R>(0, vec.y, 0),
                    Vector4<R>(0, 0, vec.z));
}

template<Real R>
Matrix3<R> Matrix3<R>::Rotate(Mat mat, const Real auto& theta, Vector3<R> vec)
{
    auto c = std::cos(theta);
    auto s = std::sin(theta);
    auto v = Vector3<R>::Normalize(vec);

    return mat * Mat(
                         c + v.x * v.x * (1 - c), v.x * v.y * (1 - c) - v.z * s, v.x * v.z * (1 - c) + v.y * s,
                         v.x * v.y * (1 - c) + v.z * s, c + v.y * v.y * (1 - c), v.y * v.z * (1 - c) - v.x * s,
                         v.x * v.z * (1 - c) - v.y * s, v.z * v.y * (1 - c) + v.x * s, c + v.z * v.z * (1 - c));
}

template<Real R>
Matrix3<R> Matrix3<R>::RotateX(const Float theta)
{
    return Mat(
            Vector3<R>(1, 0, 0),
            Vector3<R>(0, std::cos(theta), std::sin(theta)),
            Vector3<R>(0, -std::sin(theta), std::cos(theta)));
}

template<Real R>
Matrix3<R> Matrix3<R>::RotateY(const Float theta)
{
    return Mat(
            Vector3<R>(std::cos(theta), 0, -std::sin(theta)),
            Vector3<R>(0, 1, 0),
            Vector3<R>(std::sin(theta), 0, std::cos(theta)));
}

template<Real R>
Matrix3<R> Matrix3<R>::RotateZ(const Float theta)
{
    return Matrix3<R>(
            Vector3<R>(std::cos(theta), std::sin(theta), 0),
            Vector3<R>(-std::sin(theta), std::cos(theta), 0),
            Vector3<R>(0, 0, 1));
}

template<Real R>
Matrix3<R>::Vec Matrix3<R>::GetCol(UInt index) const
{
    return (*this)[index];
}

template<Real R>
Matrix3<R>::Matrix3(const Vec& col_1, const Vec& col_2, const Vec& col_3)
{
    value[0] = col_1;
    value[1] = col_2;
    value[2] = col_3;
}

template<Real R>
Matrix3<R>::Matrix3(R m11, R m21, R m31,
                    R m12, R m22, R m32,
                    R m13, R m23, R m33)
    : Matrix3(
              Vec(m11, m12, m13),
              Vec(m21, m22, m23),
              Vec(m31, m32, m33))
{
}

template<Real R>
Matrix3<R>::Matrix3(R r)
    : Matrix3(
              Vec(r, 0, 0),
              Vec(0, r, 0),
              Vec(0, 0, r))
{
}

template<Real R>
auto Matrix3<R>::operator*(Mat m) -> Mat
{
    Mat result(0);
    for (Int8 i = 0; i < 3; i++)
    {
        for (Int8 j = 0; j < 3; j++)
        {
            R r_ji{};
            for (Int8 k = 0; k < 3; k++)
            {
                r_ji += m[j][k] * value[k][i];
            }
            result[j][i] = r_ji;
        }
    }
    return result;
}

template<Real R>
Vector3<R> Matrix3<R>::operator*(Vector3<R> v)
{
    return Vec(
            (*this)[0][0] * v[0] + (*this)[0][1] * v[1] + (*this)[0][2] * v[2],
            (*this)[1][0] * v[0] + (*this)[1][1] * v[1] + (*this)[1][2] * v[2],
            (*this)[2][0] * v[0] + (*this)[2][1] * v[1] + (*this)[2][2] * v[2]);
}

template<Real R>
Vector3<R>& Matrix3<R>::operator[](std::size_t i)
{
    return value[i];
}

#undef O_REAL_R