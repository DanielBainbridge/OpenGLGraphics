#include "Camera.h"
void Camera::UpdateCamera(float deltaTime, GLFWwindow window)
{
	//move position here
	//move angle

	if (glfwGetKey(window, GLFW_KEY_W)) {

	}
}

glm::mat4 Camera::GetViewMatrix()
{
	float thertaRad = glm::radians(theta);
	float phiRad = glm::radians(phi);
	glm::vec3 forward(cos(phiRad) * cos(thertaRad), sin(phiRad), cos(phiRad * sin(thertaRad)));

	return glm::lookAt(position, position + forward, glm::vec3(0,1,0));
}

glm::mat4 Camera::GetProjectionMatrix(float width, float height)
{
	return glm::perspective(fieldOfView, width/height, nearClipPlane, farClipPlane);
}
