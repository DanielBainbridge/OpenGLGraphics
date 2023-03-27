#include "Application.h"
#include "Camera.h"
#include "GLFWCallbacks.h"
#include <iostream>

Application::Application() {
	StartUp();
}
Application* Application::s_instance{};


bool Application::StartUp() {
	s_instance = this;
	if (!glfwInit())
		return -1;

	window = glfwCreateWindow(windowWidth, windowHeight, windowName.c_str(), nullptr, nullptr);
	if (!window) {
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);

	if (!gladLoadGL())
		return -1;

	glfwSetCursorPosCallback(window, &Application::SetMousePosition);
	glfwSetWindowSizeCallback(window, WindowResizeCallback);


	//Load shader
	shader.LoadFromFiles("SimpleShader.vert", "SimpleShader.frag");
	shader.Enable();
	
	glGenBuffers(1, &bufferID);
	glBindBuffer(GL_ARRAY_BUFFER, bufferID);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);

	glEnable(GL_DEPTH_TEST);
	
	glad_glClearColor(0, 0, 0, 1);

	//setup camera
	camera = new Camera(3.141592 / 6, 0.01, 15000);
	camera->SetPosition(glm::vec3(-750, 0, -750));
}

bool Application::Run() {
	//update window size
	glfwGetWindowSize(window, &windowWidth, &windowHeight);

	//update delta time
	float currentTime = (float)glfwGetTime();
	deltaTime = currentTime - lastTime;
	lastTime = currentTime;

	//update camera inside application
	camera->UpdateCamera(deltaTime, window);
	//call virtual update that we write in applications
	Update();

	//update mouse position
	lastMousePosition = mousePosition;
	return glfwWindowShouldClose(window) == false && glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS;
}

void Application::Render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glBindBuffer(GL_ARRAY_BUFFER, bufferID);
	//set matrix transform of stuff

	Draw();

	//shader
	//set transform matrix from camera
	shader.SetMatrixUniform("transformMatrix", camera->GetProjectionMatrix(windowWidth, windowHeight) * camera->GetViewMatrix());


	glfwSwapBuffers(window);
	glfwPollEvents();
}

void Application::ShutDown()
{
	glfwTerminate();
}


void Application::SetMousePosition(GLFWwindow* window, double x, double y) {
	s_instance->mousePosition.x = float(x);
	s_instance->mousePosition.y = float(y);
}