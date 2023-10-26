#pragma once

#include "../ew/ewMath/mat4.h"
#include "../ew/ewMath/vec3.h"
#include "transformations.h"

namespace gs
{
	struct CameraControls
	{
		double prevMouseX, prevMouseY;
		float yaw = 0, pitch = 0;
		float mouseSensitivity = 0.1f;
		bool firstMouse = true;
		float moveSpeed = 5.0f;
	};
	
	struct Camera
	{
		ew::Vec3 position;
		ew::Vec3 target;
		float fov;
		float aspectPlane;
		float nearPlane;
		float farPlane;
		bool orthographic;
		float orthoSize;
		ew::Mat4 ViewMatrix()
		{
			return Lookat(position, target, ew::Vec3(0, 1, 0));
		}
		ew::Mat4 ProjectionMatrix()
		{
			if (orthographic)
				return Orthographic(orthoSize, aspectPlane, nearPlane, farPlane);
			else
				return Perspective(fov, aspectPlane, nearPlane, farPlane);
		}
	};
}