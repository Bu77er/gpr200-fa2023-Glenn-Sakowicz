#include <stdio.h>
#include <math.h>

#include <ew/external/glad.h>
#include <ew/ewMath/ewMath.h>
#include <GLFW/glfw3.h>
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

#include <ew/shader.h>
#include <ew/procGen.h>
#include <ew/transform.h>

#include <gs/transformations.h>



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
struct CameraControls
{
	double prevMouseX, prevMouseY;
	float yaw = 0, pitch = 0;
	float mouseSensitivity = 0.1f;
	bool firstMouse = true;
	float moveSpeed = 5.0f;
};


void framebufferSizeCallback(GLFWwindow* window, int width, int height);

void moveCamera(GLFWwindow* window, Camera* camera, CameraControls* controls, float deltaTime)
{
	if (!glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_2))
	{
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
		controls->firstMouse = true;
		return;
	}

	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	double mouseX, mouseY;
	glfwGetCursorPos(window, &mouseX, &mouseY);

	if (controls->firstMouse)
	{
		controls->firstMouse = false;
		controls->prevMouseX = mouseX;
		controls->prevMouseY = mouseY;
	}

	float xOffset = mouseX - controls->prevMouseX;
	float yOffset = controls->prevMouseY - mouseY;
	controls->prevMouseX = mouseX;
	controls->prevMouseY = mouseY;

	xOffset *= controls->mouseSensitivity;
	yOffset *= controls->mouseSensitivity;

	controls->yaw += xOffset;
	controls->pitch += yOffset;


	if (controls->pitch > 89.0f)
		controls->pitch = 89.0f;
	if (controls->pitch < -89.0f)
		controls->pitch = -89.0f;

	controls->prevMouseX = mouseX;
	controls->prevMouseY = mouseY;

	ew::Vec3 forward;
	forward.x = cos(ew::Radians(controls->yaw) * cos(ew::Radians(controls->pitch)));
	forward.y = sin(ew::Radians(controls->pitch));
	forward.z = sin(ew::Radians(controls->yaw) * cos(ew::Radians(controls->pitch)));
	camera->target = camera->position + forward;

	ew::Vec3 up = ew::Vec3(0,1,0);
	ew::Vec3 right = ew::Normalize(ew::Cross(forward, up));

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		camera->position += controls->moveSpeed * forward;
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		camera->position -= controls->moveSpeed * forward;
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		camera->position -= right * controls->moveSpeed;
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		camera->position += right * controls->moveSpeed;
	if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
		camera->position += up * controls->moveSpeed;
	if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
		camera->position -= up * controls->moveSpeed;


	if (glfwGetKey(window, GLFW_KEY_W))
		camera->position += forward * controls->moveSpeed * deltaTime;

}

//Projection will account for aspect ratio!
const int SCREEN_WIDTH = 1080;
const int SCREEN_HEIGHT = 720;

const int NUM_CUBES = 4;
ew::Transform cubeTransforms[NUM_CUBES];

int main() {
	printf("Initializing...");
	if (!glfwInit()) {
		printf("GLFW failed to init!");
		return 1;
	}
	
	GLFWwindow* window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Camera", NULL, NULL);
	if (window == NULL) {
		printf("GLFW failed to create window");
		return 1;
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);

	if (!gladLoadGL(glfwGetProcAddress)) {
		printf("GLAD Failed to load GL headers");
		return 1;
	}

	//Initialize ImGUI
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init();

	//Enable back face culling
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);

	//Depth testing - required for depth sorting!
	glEnable(GL_DEPTH_TEST);

	ew::Shader shader("assets/vertexShader.vert", "assets/fragmentShader.frag");
	
	//Cube mesh
	ew::Mesh cubeMesh(ew::createCube(0.5f));

	//Cube positions
	for (size_t i = 0; i < NUM_CUBES; i++)
	{
		cubeTransforms[i].position.x = i % (NUM_CUBES / 2) - 0.5;
		cubeTransforms[i].position.y = i / (NUM_CUBES / 2) - 0.5;
	}
	Camera camera;
	CameraControls cameraControls;
	float prevTime;

	while (!glfwWindowShouldClose(window)) {
		glfwPollEvents();

		float time = (float)glfwGetTime();
		float deltaTime = time - prevTime;
		prevTime = time;

		moveCamera(window, &camera, &cameraControls, deltaTime);

		glClearColor(0.3f, 0.4f, 0.9f, 1.0f);
		//Clear both color buffer AND depth buffer
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//Set uniforms
		shader.use();

		//TODO: Set model matrix uniform
		for (size_t i = 0; i < NUM_CUBES; i++)
		{
			//Construct model matrix
			shader.setMat4("_Model", cubeTransforms[i].getModelMatrix());
			cubeMesh.draw();
		}

		//Render UI
		{
			ImGui_ImplGlfw_NewFrame();
			ImGui_ImplOpenGL3_NewFrame();
			ImGui::NewFrame();

			ImGui::Begin("Settings");
			ImGui::Text("Cubes");
			for (size_t i = 0; i < NUM_CUBES; i++)
			{
				ImGui::PushID(i);
				if (ImGui::CollapsingHeader("Transform")) {
					ImGui::DragFloat3("Position", &cubeTransforms[i].position.x, 0.05f);
					ImGui::DragFloat3("Rotation", &cubeTransforms[i].rotation.x, 1.0f);
					ImGui::DragFloat3("Scale", &cubeTransforms[i].scale.x, 0.05f);
				}
				ImGui::PopID();
			}
			ImGui::Text("Camera");
			ImGui::End();
			
			ImGui::Render();
			ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
		}

		glfwSwapBuffers(window);
	}
	printf("Shutting down...");
}

void framebufferSizeCallback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}