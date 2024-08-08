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

	Mat operator*(Mat m);
	Vec operator*(Vector4<R> v);
	Vec& operator[](std::size_t i);
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
	static std::array<R, 4 * 4> ValueArray(Mat mat);
	static Matrix4 Translate(Mat mat, Vector3<R> vec);
	static Matrix4 Scale(Mat mat, Vector3<R> vec);
	static Matrix4 Rotate(Mat mat, const Real auto& theta, Vector3<R> vec);
	static Matrix4 RotateX(Float theta);
	static Matrix4 RotateY(Float theta);
	static Matrix4 RotateZ(Float theta);
	static Matrix4 Perspective(const Real auto& view, const Real auto& aspect, const Real auto& near, const Real auto& far);
	static Matrix4 Orthographic(
		const Real auto& left, const Real auto& right,
		const Real auto& bottom, const Real auto& top,
		const Real auto& near, const Real auto& far
	);
	static Matrix4 LookAt(Vector3<R> const& eye, Vector3<R> const& center, Vector3<R> const& up);

private:
	Vec value[4];

};


using Matrix4f = Matrix4<Float>;
using Matrix4d = Matrix4<Double>;

#include "Nenuphar/Math/Matrix4.inl"