#pragma once
#include "ewMath/transformations.h"
#include "ewMath/ewMath.h"
namespace ew {

	struct Camera {
		ew::Vec3 position = ew::Vec3(0.0f, 0.0f, 5.0f);
		ew::Vec3 target = ew::Vec3(0.0f);

		float fov = 60.0f;
		float nearPlane = 0.01f;
		float farPlane = 100.0f;
		bool orthographic = false;
		float orthoHeight = 6.0f;
		float aspectRatio = 1.77f;

		inline ew::Mat4 ViewMatrix()const {
			return ew::LookAt(position, target, ew::Vec3(0, 1, 0));
		}
		inline ew::Mat4 ProjectionMatrix()const {

			if (orthographic) {
				return ew::Orthographic(orthoHeight, aspectRatio, nearPlane, farPlane);
			}
			else {
				return ew::Perspective(ew::Radians(fov), aspectRatio, nearPlane, farPlane);
			}
		}
	};

}
