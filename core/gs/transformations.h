#pragma once
#include "../ew/ewMath/mat4.h"
#include "../ew/ewMath/vec3.h"

namespace gs
{
	inline ew::Mat4 Idenitiy()
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

		}
	};
}