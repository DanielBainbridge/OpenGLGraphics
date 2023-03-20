#include "Application.h"

#include "Utility.h"
#include <iostream>
#include "ShaderProgram.h"
#include "Mesh.h"
#include "Camera.h"

int main() {

	//new Startup to utilise Application class, easy entry point to swap out program

	/*Application newApp;

	newApp.StartUp();
	while (newApp.Run()) {
		newApp.Draw();
	}*/

	//

	Mesh quadMesh;
	Mesh literallyQuadMesh;

	Camera cam = Camera(90, 0.01f, 10000);
	cam.SetPosition(glm::vec3(3000, 1800, 3000));


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

		quadMesh.InitialiseFromFile("characters\\Marksman\\Marksman.fbx");
	//loop
	while (!glfwWindowShouldClose(window)) {



		currentTime = (float)glfwGetTime();
		deltaTime = currentTime - lastTime;
		lastTime = currentTime;

		cam.UpdateCamera(deltaTime, window);

		incrementer += deltaTime * 2.0f;

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

		//simpleShader->SetMatrixUniform("transformMatrix", projection * view * rotation);
		simpleShader->SetMatrixUniform("transformMatrix", cam.GetProjectionMatrix(width, height) * cam.GetViewMatrix() * rotation);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}