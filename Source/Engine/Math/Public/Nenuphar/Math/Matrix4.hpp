#pragma once

#include <array>

#include "Nenuphar/Math/CommonMath.hpp"
#include "Nenuphar/Math/Vector4.hpp"
#include "Nenuphar/Math/Vector3.hpp"

template<Real R>
struct Matrix4
{
	using Mat = Matrix4<R>;
	using Vec = Vector4<R>;

	Mat operator*(const Mat& m) const;
	Vec operator*(const Vector4<R>& v) const;
	Vec& operator[](std::size_t i);
    const Vec& operator[](std::size_t i) const;
    Vec GetCol(UInt index) const;

    Matrix4() = default;
	Matrix4(R r);
	Matrix4(
		R m11, R m21, R m31, R m41,
		R m12, R m22, R m32, R m42,
		R m13, R m23, R m33, R m43,
		R m14, R m24, R m34, R m44);
	Matrix4(const Vec& col_1, const Vec& col_2, const Vec& col_3, const Vec& col_4);

	static Matrix4 Identity();
	static std::array<R, 4 * 4> ValueArray(const Mat& mat);
    static Matrix4 Translate(const Mat& mat, const Vector3<R>& vec);
    static Matrix4 Scale(const Mat& mat, const Vector3<R>& vec);
    static Matrix4 Rotate(const Mat& mat, const Real auto& theta, const Vector3<R>& vec);
	static Matrix4 RotateX(const Float& theta);
	static Matrix4 RotateY(const Float& theta);
	static Matrix4 RotateZ(const Float& theta);
	static Matrix4 Perspective(const Real auto& view, const Real auto& aspect, const Real auto& near, const Real auto& far);
	static Matrix4 Orthographic(
		const Real auto& left, const Real auto& right,
		const Real auto& bottom, const Real auto& top,
		const Real auto& near, const Real auto& far
	);
    static Matrix4 LookAt(const Vector3<R>& eye, const Vector3<R>& center, const Vector3<R>& up);

private:
	Vec value[4];

};


using Matrix4f = Matrix4<Float>;
using Matrix4d = Matrix4<Double>;

#include "Nenuphar/Math/Matrix4.inl"