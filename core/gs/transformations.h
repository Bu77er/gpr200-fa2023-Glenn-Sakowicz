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