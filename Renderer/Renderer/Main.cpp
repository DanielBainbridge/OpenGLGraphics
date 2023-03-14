#include "Graphics.h"
#include "Utility.h"
#include <glm.hpp>
#include <iostream>
#include "ShaderProgram.h"

int main() {

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

	float someFloats[]{
		0,0,
		0,1,
		1,0
	};
	
	glBindBuffer(GL_ARRAY_BUFFER, bufferID);
	glBufferData(GL_ARRAY_BUFFER, sizeof(someFloats), someFloats, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glEnableVertexAttribArray(0);


	float incrementer = 0;
	float shittyRedValue = 0;
	float shittyBlueValue = 0;
	float shittyGreenValue = 0;


	//loop
	while (!glfwWindowShouldClose(window)) {
		glClear(GL_COLOR_BUFFER_BIT);

		glBindBuffer(GL_ARRAY_BUFFER, bufferID);

		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, 0);

		simpleShader->Enable();
		simpleShader->SetFloatUniform("setFloat", sin(currentTime));


		glDrawArrays(GL_TRIANGLES, 0, 3);

		glDrawArrays(GL_TRIANGLES, 0, 3);


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