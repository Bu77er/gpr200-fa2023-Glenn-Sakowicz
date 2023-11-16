#include "cameraController.h"
namespace ew {
	void CameraController::Move(GLFWwindow* window, ew::Camera* camera, float deltaTime) {
		//Only allow movement if right mouse is held
		if (!glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_2)) {
			//Release cursor
			glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
			firstMouse = true;
			return;
		}
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	
		//MOUSE AIMING
		{
			double mouseX, mouseY;
			glfwGetCursorPos(window, &mouseX, &mouseY);

			//First frame, set prevMouse values
			if (firstMouse) {
				firstMouse = false;
				prevMouseX = mouseX;
				prevMouseY = mouseY;
			}

			float mouseDeltaX = (float)(mouseX - prevMouseX);
			float mouseDeltaY = (float)(mouseY - prevMouseY);

			prevMouseX = mouseX;
			prevMouseY = mouseY;

			//Change yaw and pitch (degrees)
			yaw += mouseDeltaX * mouseSensitivity;
			pitch -= mouseDeltaY * mouseSensitivity;
			pitch = ew::Clamp(pitch, -89.0f, 89.0f);

		}
		//KEYBOARD MOVEMENT
		{
			float yawRad = ew::Radians(yaw);
			float pitchRad = ew::Radians(pitch);

			//Construct forward, right, and up vectors
			ew::Vec3 forward;
			forward.x = cosf(pitchRad) * sinf(yawRad);
			forward.y = sinf(pitchRad);
			forward.z = cosf(pitchRad) * -cosf(yawRad);
			forward = ew::Normalize(forward);

			ew::Vec3 right = ew::Normalize(ew::Cross(forward, ew::Vec3(0, 1, 0)));
			ew::Vec3 up = ew::Normalize(ew::Cross(right, forward));

			//Keyboard movement
			float speed = glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) ? sprintMoveSpeed : moveSpeed;
			float moveDelta = speed * deltaTime;
			if (glfwGetKey(window, GLFW_KEY_W)) {
				camera->position += forward * moveDelta;
			}
			if (glfwGetKey(window, GLFW_KEY_S)) {
				camera->position -= forward * moveDelta;
			}
			if (glfwGetKey(window, GLFW_KEY_D)) {
				camera->position += right * moveDelta;
			}
			if (glfwGetKey(window, GLFW_KEY_A)) {
				camera->position -= right * moveDelta;
			}
			if (glfwGetKey(window, GLFW_KEY_E)) {
				camera->position += up * moveDelta;
			}
			if (glfwGetKey(window, GLFW_KEY_Q)) {
				camera->position -= up * moveDelta;
			}

			//Camera will now look at a position along this forward axis
			camera->target = camera->position + forward;
		}
	}
}