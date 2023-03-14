#define GLFW_INCLUDE_NONE
#include "glfw3.h"
#include "glad.h"
#include "Utility.h"
#include <glm.hpp>
#include <iostream>


int main() {

	float currentTime = 0;
	float deltaTime = 0;
	float lastTime = 0;
	
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

	std::cout << LoadFileAsString("printThis.txt") << std::endl;

	float incrementer = 0;
	float shittyRedValue = 0;
	float shittyBlueValue = 0;
	float shittyGreenValue = 0;
	while (!glfwWindowShouldClose(window)) {
		glClear(GL_COLOR_BUFFER_BIT);

		currentTime = glfwGetTime();
		deltaTime = currentTime - lastTime;
		lastTime = currentTime;

		incrementer += deltaTime * 2.0f;

		shittyRedValue = glm::sin(incrementer);
		shittyBlueValue = glm::cos(-incrementer);
		shittyGreenValue = glm::sin(-incrementer);

		//make screen transition betweeen some colours

		glad_glClearColor(shittyRedValue, shittyGreenValue, shittyBlueValue, 1);


		//Put some kind of text file in your working directory, and then test the LoadFileAsString function you wrote in step three to make sure your function, and the working directory, are both set up properly.


		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}