#pragma once
#include <GLFW/glfw3.h>
#include "camera.h"

namespace ew {
	struct CameraController {
		float moveSpeed = 3.0f; //Default speed
		float sprintMoveSpeed = 6.0f; //Speed when left shift is held
		float mouseSensitivity = 0.1f; //mouse delta to degrees. Higher values = faster
		float yaw = 0.0f; //Degrees
		float pitch = 0.0f; //Degrees
		double prevMouseX = 0; //Stores previous mouse X position each frame
		double prevMouseY = 0; //Stores previous mouse Y position each frame
		bool firstMouse = true; //Used to get first frame mouse position

		//Using input from window, aim and rotate camera
		void Move(GLFWwindow* window, ew::Camera* camera, float deltaTime);
	};
}