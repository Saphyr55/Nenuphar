#include "Nenuphar/Math/Matrix4.hpp"

#include <cassert>
#include <cmath>

template<Real R>
Matrix4<R> Matrix4<R>::Identity() {
  return Matrix4(1);
}

template<Real R>
std::array<R, 4 * 4> Matrix4<R>::ValueArray(const Mat& mat) {
  std::array<R, 4 * 4> content;
  for (Int8 i = 0; i < 4; i++) {
    for (Int8 j = 0; j < 4; j++) {
      content[i * 4 + j] = mat[i][j];
    }
  }
  return content;
}

template<Real R>
Matrix4<R> Matrix4<R>::Translate(const Mat& mat, const Vector3<R>& vec) {
  Mat transformation_mat(1);
  transformation_mat[3] = Vector4<R>(vec, 1);
  return mat * transformation_mat;
}

template<Real R>
Matrix4<R> Matrix4<R>::Scale(const Mat& mat, const Vector3<R>& vec) {
  return mat * Mat(Vector4<R>(vec.x, 0, 0, 0), Vector4<R>(0, vec.y, 0, 0),
                   Vector4<R>(0, 0, vec.z, 0), Vector4<R>(0, 0, 0, 1));
}

template<Real R>
Matrix4<R> Matrix4<R>::Rotate(const Mat& mat,
                              const Real auto& theta,
                              const Vector3<R>& vec) {
  auto c = std::cos(theta);
  auto s = std::sin(theta);
  auto v = Vector3<R>::Normalize(vec);

  return mat * Mat(c + v.x * v.x * (1 - c), v.x * v.y * (1 - c) - v.z * s,
                   v.x * v.z * (1 - c) + v.y * s, 0,
                   v.x * v.y * (1 - c) + v.z * s, c + v.y * v.y * (1 - c),
                   v.y * v.z * (1 - c) - v.x * s, 0,
                   v.x * v.z * (1 - c) - v.y * s, v.z * v.y * (1 - c) + v.x * s,
                   c + v.z * v.z * (1 - c), 0, 0, 0, 0, 1);
}

template<Real R>
Matrix4<R> Matrix4<R>::RotateX(const Float& theta) {
  return Mat(Vector4<R>(1, 0, 0, 0),
             Vector4<R>(0, std::cos(theta), std::sin(theta), 0),
             Vector4<R>(0, -std::sin(theta), std::cos(theta), 0),
             Vector4<R>(0, 0, 0, 1));
}

template<Real R>
Matrix4<R> Matrix4<R>::RotateY(const Float& theta) {
  return Mat(Vector4<R>(std::cos(theta), 0, -std::sin(theta), 0),
             Vector4<R>(0, 1, 0, 0),
             Vector4<R>(std::sin(theta), 0, std::cos(theta), 0),
             Vector4<R>(0, 0, 0, 1));
}

template<Real R>
Matrix4<R> Matrix4<R>::RotateZ(const Float& theta) {
  return Matrix4<R>(Vector4<R>(std::cos(theta), std::sin(theta), 0, 0),
                    Vector4<R>(-std::sin(theta), std::cos(theta), 0, 0),
                    Vector4<R>(0, 0, 1, 0), Vector4<R>(0, 0, 0, 1));
}

template<Real R>
Matrix4<R> Matrix4<R>::Perspective(const Real auto& view,
                                   const Real auto& aspect,
                                   const Real auto& near_,
                                   const Real auto& far_) {
  Mat result(0);

  R const tanHalfFovy = std::tan(view / static_cast<R>(2));

  result[0][0] = R(1) / (tanHalfFovy * aspect);
  result[1][1] = R(1) / tanHalfFovy;
  result[2][2] = R(-far_ - near_) / (far_ - near_);
  result[3][2] = -R(2 * near_ * far_) / (far_ - near_);
  result[2][3] = -R(1);
  return result;
}

template<Real R>
Matrix4<R> Matrix4<R>::Orthographic(const Real auto& left,
                                    const Real auto& right,
                                    const Real auto& bottom,
                                    const Real auto& top,
                                    const Real auto& near_,
                                    const Real auto& far_) {
  assert(far_ - near_ != 0);
  Mat result(1);
  result[0][0] = R(2) / (right - left);
  result[1][1] = R(2) / (top - bottom);
  result[2][2] = -R(2) / (far_ - near_);
  result[3][0] = -R(right + left) / (right - left);
  result[3][1] = -R(top + bottom) / (top - bottom);
  result[3][2] = -R(far_ + near_) / (far_ - near_);
  return result;
}

template<Real R>
Matrix4<R> Matrix4<R>::LookAt(const Vector3<R>& eye,
                              const Vector3<R>& center,
                              const Vector3<R>& up) {
  auto f = Vector3<R>::Normalize(center - eye);
  auto s = Vector3<R>::Normalize(Vector3<R>::Cross(f, up));
  auto u = Vector3<R>::Cross(s, f);

  Mat result(1);
  result[0][0] = s.x;
  result[1][0] = s.y;
  result[2][0] = s.z;
  result[0][1] = u.x;
  result[1][1] = u.y;
  result[2][1] = u.z;
  result[0][2] = f.x;
  result[1][2] = f.y;
  result[2][2] = f.z;
  result[3][0] = -s.Dot(eye);
  result[3][1] = -u.Dot(eye);
  result[3][2] = -f.Dot(eye);
  return result;
}

template<Real R>
Vector4<R> Matrix4<R>::GetCol(UInt index) const {
  return (*this)[index];
}

template<Real R>
Matrix4<R>::Matrix4(const Vec& col_1,
                    const Vec& col_2,
                    const Vec& col_3,
                    const Vec& col_4) {
  value[0] = col_1;
  value[1] = col_2;
  value[2] = col_3;
  value[3] = col_4;
}

template<Real R>
Matrix4<R>::Matrix4(R m11,
                    R m21,
                    R m31,
                    R m41,
                    R m12,
                    R m22,
                    R m32,
                    R m42,
                    R m13,
                    R m23,
                    R m33,
                    R m43,
                    R m14,
                    R m24,
                    R m34,
                    R m44)
    : Matrix4(Vec(m11, m12, m13, m14),
              Vec(m21, m22, m23, m24),
              Vec(m31, m32, m33, m34),
              Vec(m41, m42, m43, m44)) {}

template<Real R>
Matrix4<R>::Matrix4(R r)
    : Matrix4(Vec(r, 0, 0, 0),
              Vec(0, r, 0, 0),
              Vec(0, 0, r, 0),
              Vec(0, 0, 0, r)) {}

template<Real R>
Matrix4<R> Matrix4<R>::operator*(const Mat& m) const {
  Mat result(0);
  for (Int8 i = 0; i < 4; i++) {
    for (Int8 j = 0; j < 4; j++) {
      R r_ji{};
      for (Int8 k = 0; k < 4; k++) {
        r_ji += m[j][k] * value[k][i];
      }
      result[j][i] = r_ji;
    }
  }
  return result;
}

template<Real R>
Vector4<R> Matrix4<R>::operator*(const Vector4<R>& v) const {
  return Vec((*this)[0][0] * v[0] + (*this)[0][1] * v[1] +
                 (*this)[0][2] * v[2] + (*this)[0][3] * v[3],
             (*this)[1][0] * v[0] + (*this)[1][1] * v[1] +
                 (*this)[1][2] * v[2] + (*this)[1][3] * v[3],
             (*this)[2][0] * v[0] + (*this)[2][1] * v[1] +
                 (*this)[2][2] * v[2] + (*this)[2][3] * v[3],
             (*this)[3][0] * v[0] + (*this)[3][1] * v[1] +
                 (*this)[3][2] * v[2] + (*this)[3][3] * v[3]);
}

template<Real R>
const Vector4<R>& Matrix4<R>::operator[](std::size_t i) const {
  return value[i];
}

template<Real R>
Vector4<R>& Matrix4<R>::operator[](std::size_t i) {
  return value[i];
}

#undef O_REAL_R