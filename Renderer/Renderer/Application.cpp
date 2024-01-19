#include "Application.h"
#include "Camera.h"
#include "GLFWCallbacks.h"
#include <iostream>
#include "Texture.h"

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
	phongShader.LoadFromFiles("Shaders\\normalShader.vert", "Shaders\\normalShader.frag");
	phongShader.Enable();
	PBRShader.LoadFromFiles("Shaders\\PBRSkinnedShaderMask.vert", "Shaders\\PBRSkinnedShaderMask.frag");
	PBRShader.Enable();
	screenShader.LoadFromFiles("Shaders\\renderBufferTest.vert", "Shaders\\renderBufferTest.frag");
	screenShader.Enable();
	screenShader.bindUniform("screenTexture", 0);

	//set up screenspace quad
	float quadVertices[] = {

		1.0f, -1.0f, 1.0f, 0.0f,
		-1.0f, -1.0f,  0.0f, 0.0f,
		-1.0f,  1.0f,  0.0f, 1.0f,

		 1.0f,  1.0f,  1.0f, 1.0f,
		 1.0f, -1.0f,  1.0f, 0.0f,
		-1.0f,  1.0f,  0.0f, 1.0f
	};
	glGenBuffers(1, &textureQuadVBO);
	glGenVertexArrays(1, &textureQuadVAO);
	glBindVertexArray(textureQuadVAO);
	glBindBuffer(GL_ARRAY_BUFFER, textureQuadVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), &quadVertices, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));


	//create frame buffer
	glGenFramebuffers(1, &bufferID);
	glBindFramebuffer(GL_FRAMEBUFFER, bufferID);

	//create Texture
	texture = new Texture();
	texture->CreateScreenSpaceTexture(windowWidth, windowHeight);
	

	//create render buffer object
	glGenRenderbuffers(1, &renderbufferObject);
	glBindRenderbuffer(GL_RENDERBUFFER, renderbufferObject);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, windowWidth, windowHeight);
	glBindRenderbuffer(GL_RENDERBUFFER, 0);

	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, renderbufferObject);

	//check that the frame buffer is complete
	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		std::cout << "ERROR::FRAMEBUFFER:: Framebuffer is not complete!" << std::endl;

	//set back to main buffer
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);

	glEnable(GL_DEPTH_TEST);
	//change front face to be clockwise
	glFrontFace(GL_CW);
	//cull back faces
	glEnable(GL_CULL_FACE);
	//glEnable(GL_STENCIL);
	
	glad_glClearColor(0.65f, 0.65f, 0.65f, 1);
	// draw as wireframe
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);


	//setup camera
	camera = new Camera(3.141592 / 6, 1.5f, 16000);
	camera->SetPosition(glm::vec3(0, 0, 0));
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
	//first pass draw the application
	glBindFramebuffer(GL_FRAMEBUFFER, bufferID);
	glEnable(GL_DEPTH_TEST);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//Virtual, In most cases, cursive, draws scene, draws scene models
	Draw();


	//bind back to default frame buffer
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	//disable depth test to ensure nothing renders on top of quad
	glDisable(GL_DEPTH_TEST);
	//clear colour
	glClear(GL_COLOR_BUFFER_BIT);

	//enable screenspace shader
	screenShader.Enable();
	glBindVertexArray(textureQuadVAO); //bind screen size quad
	texture->Bind(1);
	screenShader.bindUniform("screenTexture", 1);
	glDrawArrays(GL_TRIANGLES, 0, 6);

	DrawIMGUI();
	//swap window buffers and poll events
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