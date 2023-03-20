#include "Application.h"
#include "Camera.h"

bool Application::StartUp() {
	if (!glfwInit())
		return -1;

	window = glfwCreateWindow(windowWidth, windowHeight, windowName.c_str(), nullptr, nullptr);
	if (!window) {
		glfwTerminate();
		return -1;
	}
	s_instance = this;

	glfwMakeContextCurrent(window);

	if (!gladLoadGL())
		return -1;

	glfwSetCursorPosCallback(window, &Application::SetMousePosition);
}

bool Application::Run() {
	//update window size
	glfwGetWindowSize(window, &windowWidth, &windowHeight);

	//update delta time
	float currentTime = (float)glfwGetTime();
	deltaTime = currentTime - lastTime;
	lastTime = currentTime;

	//update mouse position
	lastMousePosition = mousePosition;

	//update camera inside application
	camera.UpdateCamera(deltaTime, window);

	//call virtual update that we write in applications
	Update();

	return glfwWindowShouldClose(window) == false && glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS;
}

void Application::Render()
{
	Draw();
}


void Application::SetMousePosition(GLFWwindow* window, double x, double y) {
	s_instance->mousePosition.x = float(x);
	s_instance->mousePosition.y = float(y);
}