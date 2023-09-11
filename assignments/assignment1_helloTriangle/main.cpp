#include <stdio.h>
#include <math.h>

#include <ew/external/glad.h>
#include <ew/ewMath/ewMath.h>
#include <GLFW/glfw3.h>

const int SCREEN_WIDTH = 1080;
const int SCREEN_HEIGHT = 720;

int main() {
	printf("Initializing...");
	if (!glfwInit()) {
		printf("GLFW failed to init!");
		return 1;
	}

	const char* vertexShaderSource = R"(
		#version 450
		layout(location = 0) in vec3 vPos;
		void main(){
		gl_Position = vec4(vPos,1.0);
		}
	)";
	const char* fragmentShaderSource = R"(
		#version 450
		out vec4 FragColor;
		void main(){
		FragColor = vec4(1.0,0.0,0.0,1.0);
		}
	)";
	const char* vertexShaderSource = R"(
	#version 450
	layout(location = 0) in vec3 vPos;
	layout(location = 1) in vec4 vColor;
	out vec4 Color;
	void main(){
		Color = vColor;
		gl_Position = vec4(vPos,1.0);
	}
)";
	const char* fragmentShaderSource = R"(
	#version 450
	out vec4 FragColor;
	in vec4 Color;
	uniform float _Time = 1.0;
	void main(){
		FragColor = Color;
	}
)";
	const char* fragmentShaderSource = R"(
	#version 450
	out vec4 FragColor;
	in vec4 Color;
	uniform float _Time;
	void main(){
		FragColor = Color * abs(sin(_Time));
	}
)";
	const char* vertexShaderSource = R"(
	#version 450
	layout(location = 0) in vec3 vPos;
	layout(location = 1) in vec4 vColor;
	out vec4 Color;
	uniform float _Time;
	void main(){
		Color = vColor;
		vec3 offset = vec3(0,sin(vPos.x + _Time),0)*0.5;
		gl_Position = vec4(vPos + offset,1.0);
	}
)";

	float vertices[9] = {
	
		-0.5, -0.5, 0.0,
		 0.5, -0.5, 0.0,
		 0.0,  0.5, 0.0 
	};

	float vertices[21] = {
		//x   //y  //z   //r  //g  //b  //a
		-0.5, -0.5, 0.0, 1.0, 0.0, 0.0, 1.0, //Bottom left
		 0.5, -0.5, 0.0, 0.0, 1.0, 0.0, 1.0, //Bottom right
		 0.0,  0.5, 0.0, 0.0, 0.0, 1.0, 1.0  //Top center
	};



	GLFWwindow* window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Hello Triangle", NULL, NULL);
	if (window == NULL) {
		printf("GLFW failed to create window");
		return 1;
	}
	glfwMakeContextCurrent(window);

	if (!gladLoadGL(glfwGetProcAddress)) {
		printf("GLAD Failed to load GL headers");
		return 1;
	}

	unsigned int vbo;
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	unsigned int vao;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	//Tell vao to pull vertex data from vbo
	glBindBuffer(GL_ARRAY_BUFFER, vbo);

	//Define position attribute (3 floats)
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, (const void*)0);
	glEnableVertexAttribArray(0);

	unsigned int createShader(GLenum shaderType, const char* sourceCode);
	unsigned int vertexShader = createShader(GL_VERTEX_SHADER, vertexShaderSource);
	unsigned int fragmentShader = createShader(GL_FRAGMENT_SHADER, fragmentShaderSource);

	unsigned int shaderProgram = glCreateProgram();
	//Attach each stage
	glAttachShader(shaderProgram, vertexShader);
	//glAttachShader(shaderProgram, geometryShader);
	glAttachShader(shaderProgram, fragmentShader);
	//Link all the stages together
	glLinkProgram(shaderProgram);

	int success;
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if (!success) {
		char infoLog[512];
		glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
		printf("Failed to link shader program: %s", infoLog);
	}
	//The linked program now contains our compiled code, so we can delete these intermediate objects
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	unsigned int createVAO(float* vertexData, int numVertices);
	
		//Create a new vertex shader object
		unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
		//Supply the shader object with source code
		glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
		//Compile the shader object
		glCompileShader(vertexShader);

		int success;
		glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
		if (!success) {
			//512 is an arbitrary length, but should be plenty of characters for our error message.
			char infoLog[512];
			glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
			printf("Failed to compile shader: %s", infoLog);
		}
	

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 7, (const void*)0);
		glEnableVertexAttribArray(0);

		//Color attribute
		glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(float) * 7, (const void*)(sizeof(float) * 3));
		glEnableVertexAttribArray(1);
	
		unsigned int shader = createShaderProgram(vertexShaderSource, fragmentShaderSource);
	
		unsigned int vao = createVAO(vertices, 3);

		float time = (float)glfwGetTime();
		//Get the location of the uniform by name
		int timeLocation = glGetUniformLocation(shader, "_Time");
		//Set the value of the variable at the location
		glUniform1f(timeLocation, time);

		glDrawArrays(GL_TRIANGLES, 0, 3);
		
		layout(location = 6) uniform float _Time; //Explicitly set location to 6
		//Option 2 - automatic
		uniform float _Time;

	while (!glfwWindowShouldClose(window)) {
		glfwPollEvents();
		glClearColor(0.3f, 0.4f, 0.9f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		glfwSwapBuffers(window);
	}
	printf("Shutting down...");

}
