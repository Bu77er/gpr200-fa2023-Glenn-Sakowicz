#pragma once
<<<<<<< HEAD
=======

>>>>>>> c2d74f52a1d9e480faddc1201be6dc0f61e26575
#include "../ew/ewMath/mat4.h"
#include "../ew/ewMath/vec3.h"

namespace gs
{
<<<<<<< HEAD
	inline ew::Mat4 Idenitiy()
=======
	inline ew::Mat4 Identity()
>>>>>>> c2d74f52a1d9e480faddc1201be6dc0f61e26575
	{
		return ew::Mat4(
			1, 0, 0, 0,
			0, 1, 0, 0,
			0, 0, 1, 0,
			0, 0, 0, 1
		);
	}
	inline ew::Mat4 Scale(ew::Vec3 s)
	{
<<<<<<< HEAD

	}
	inline ew::Mat4 RotateX(float rad)
	{

	}
	inline ew::Mat4 RotateY(float rad)
	{

	}
	inline ew::Mat4 RotateZ(float rad)
	{

	}
	inline ew::Mat4 Translate(ew::Vec3 t)
	{

	}
	struct Transform
	{
		ew::Vec3 postition = ew::Vec3(0.0f, 0.0f, 0.0f);
		ew::Vec3 rotation = ew::Vec3(0.0f, 0.0f, 0.0f);
		ew::Vec3 scale = ew::Vec3(1.0f, 1.0f, 1.0f);
		ew::Mat4 getNodeMatrix() const
		{

=======
		return ew::Mat4(
			s.x, 0, 0, 0,
			0, s.y, 0, 0,
			0, 0, s.z, 0,
			0, 0, 0, 1
		);
	}
	inline ew::Mat4 RotateX(float rad)
	{
		return ew::Mat4(
			1, 0, 0, 0,
			0, cos(rad), -sin(rad), 0,
			0, sin(rad), cos(rad), 0,
			0, 0, 0, 1
		);
	}
	inline ew::Mat4 RotateY(float rad)
	{
		return ew::Mat4(
			cos(rad), 0, sin(rad), 0,
			0, 1, 0, 0,
			-sin(rad), 0, cos(rad), 0,
			0, 0, 0, 1
		);
	}
	inline ew::Mat4 RotateZ(float rad)
	{
		return ew::Mat4(
			cos(rad), -sin(rad), 0, 0,
			sin(rad), cos(rad), 0, 0,
			0, 0, 1, 0,
			0, 0, 0, 1
		);
	}
	inline ew::Mat4 Translate(ew::Vec3 t)
	{
		return ew::Mat4(
			1, 0, 0, t.x,
			0, 1, 0, t.y,
			0, 0, 1, t.z,
			0, 0, 0, 1
		);
	}
	inline ew::Mat4 Lookat(ew::Vec3 eye, ew::Vec3 target, ew::Vec3 up)
	{
		ew::Vec3 forward = ew::Normalize(target - eye);
		ew::Vec3 right = ew::Normalize(ew::Cross(up, forward));
		up = ew::Normalize(ew::Cross(forward, right));
		ew::Mat4 matrix;

		matrix[0] = ew::Vec4(right, 0.0f);
		matrix[1] = ew::Vec4(up, 0.0f);
		matrix[2] = ew::Vec4(-forward, 0.0f);
		matrix[3] = ew::Vec4(0.0f, 0.0f, 0.0f, 1.0f);

		return matrix * Translate(-eye);
	};
	inline ew::Mat4 Orthographic(float height, float aspect, float near, float far)
	{
		float halfHeight = height / 2.0f;
		float halfWidth = halfHeight * aspect;
		float depth = far - near;

		return ew::Mat4(
			2.0f / (2.0f * halfWidth), 0.0f, 0.0f, 0.0f,
			0.0f, 2.0f / (2.0 * halfHeight), 0.0f, 0.0f,
			0.0f, 0.0f, -2.0f / depth, 0.0f,
			0.0f, 0.0f, -(far + near) / depth, 1.0f
		);
	};
	inline ew::Mat4 Perspective(float fov, float aspect, float near, float far)
	{
		float x = 1.0f / tan(fov / 2.0f);

		return ew::Mat4(
			x / aspect, 0.0f, 0.0f, 0.0f,
			0.0f, x, 0.0f, 0.0f,
			0.0f, 0.0f, (far + near) / (near - far), -1.0f,
			0.0f, 0.0f, (2.0f * far * near) / (near - far), 0.0f
		);
	};

	struct Transform
	{
		ew::Vec3 position = ew::Vec3(0.0f, 0.0f, 0.0f);
		ew::Vec3 rotation = ew::Vec3(0.0f, 0.0f, 0.0f);
		ew::Vec3 scale = ew::Vec3(1.0f, 1.0f, 1.0f);
		ew::Mat4 getModelMatrix() const
		{
			return Scale(scale);
			return RotateZ(rotation.z) * RotateX(rotation.x) * RotateY(rotation.y);
			return Translate(position);
>>>>>>> c2d74f52a1d9e480faddc1201be6dc0f61e26575
		}
	};
}