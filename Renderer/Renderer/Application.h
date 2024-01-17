#pragma once
#include "Graphics.h"
#include "ShaderProgram.h"
class Camera;
class Application {
public:

	Application();
	bool StartUp();
	bool Run();
	void Render();
	void ShutDown();
	virtual void Update() = 0;
	virtual void Draw() = 0;


	static Application* get() { return s_instance; };
	glm::vec2 GetMousePosition() { return mousePosition; };
	glm::vec2 GetMouseDelta() { return mousePosition - lastMousePosition; };
	float GetAspectRatio() { return (windowWidth / (float)windowHeight); };
	static void SetMousePosition(GLFWwindow* window, double x, double y);
	float GetDeltaTime() { return deltaTime; };
	int GetWindowWidth() { return windowWidth; };
	int GetWindowHeight() { return windowHeight; };
	Camera* camera;
	ShaderProgram phongShader;
	ShaderProgram PBRShader;
	ShaderProgram screenShader;

protected:

	static Application* s_instance;
	GLFWwindow* window;
	std::string windowName = "Window";
	int windowWidth = (int)(1920 * 0.75f), windowHeight = (int)(1080 * 0.75f);

	glm::vec2 mousePosition;


private:
	float deltaTime = 0;
	float lastTime = 0;
	glm::vec2 lastMousePosition;
	unsigned int bufferID;
	unsigned int renderbufferObject;

	unsigned int texture;

	unsigned int textureQuadVAO, textureQuadVBO;
};