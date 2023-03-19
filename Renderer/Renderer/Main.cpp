#include "Graphics.h"
#include "Utility.h"
#include <iostream>
#include "ShaderProgram.h"
#include "Mesh.h"

int main() {

	Mesh quadMesh;
	Mesh literallyQuadMesh;
	float currentTime = 0;
	float deltaTime = 0;
	float lastTime = 0;

	//make window
	GLFWwindow* window;
	if (!glfwInit())
		return -1;

	window = glfwCreateWindow(1280, 720, "Butt", nullptr, nullptr);
	if (!window) {
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);

	if (!gladLoadGL())
		return -1;

	ShaderProgram* simpleShader = new ShaderProgram();
	simpleShader->LoadFromFiles("SimpleShader.vert", "SimpleShader.frag");

	GLuint bufferID;

	glGenBuffers(1, &bufferID);

	glBindBuffer(GL_ARRAY_BUFFER, bufferID);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);

	glEnable(GL_DEPTH_TEST);

	float incrementer = 0;
	float shittyRedValue = 0;
	float shittyBlueValue = 0;
	float shittyGreenValue = 0;

	glad_glClearColor(0, 0, 0, 1);

#ifdef _DEBUG
	glEnable(GL_DEBUG_OUTPUT);
#endif

		quadMesh.InitialiseFromFile("characters\\Pyro\\pyro.fbx");
	//loop
	while (!glfwWindowShouldClose(window)) {

		currentTime = (float)glfwGetTime();
		deltaTime = currentTime - lastTime;
		lastTime = currentTime;


		incrementer += deltaTime * 2.0f;

		shittyRedValue = glm::sin(incrementer);
		shittyBlueValue = glm::cos(-incrementer);
		shittyGreenValue = glm::sin(-incrementer);

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glBindBuffer(GL_ARRAY_BUFFER, bufferID);

		simpleShader->Enable();


		quadMesh.Draw();



		float aspect;
		int width, height;
		glfwGetWindowSize(window, &width, &height);
		aspect = width / (float)height;
		
		glm::mat4 rotation = glm::rotate(glm::mat4(1), (float)glfwGetTime(), glm::vec3(0, 1, 0));
		glm::mat4 view = glm::lookAt(glm::vec3(3000, 1800, 3000), glm::vec3(0, 1250, 0), glm::vec3(0, 1, 0));

		glm::mat4 projection = glm::perspective(3.14159f / 4.0f, aspect, 1.0f, 10000.0f);

		simpleShader->SetMatrixUniform("transformMatrix", projection * view * rotation);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}