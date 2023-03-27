#include "Camera.h"
#include "Application.h"
Camera::Camera(float fieldOfView, float nearClipPlane, float farClipPlane)
{
	SetFieldOfView(fieldOfView);
	SetNearClip(nearClipPlane);
	SetFarClip(farClipPlane);
}
void Camera::UpdateCamera(float deltaTime, GLFWwindow* window)
{

	float thetaR = glm::radians(theta);
	float phiR = glm::radians(phi);

	glm::vec3 forward(cos(phiR) * cos(thetaR), sin(phiR), cos(phiR) * sin(thetaR));
	glm::vec3 right(-sin(thetaR), 0, cos(thetaR));
	glm::vec3 up(0, 1, 0);


	//move position here
	if (glfwGetKey(window, GLFW_KEY_W)) {
		position += forward * moveSpeed * deltaTime;
	}
	if (glfwGetKey(window, GLFW_KEY_A)) {
		position -= right * moveSpeed * deltaTime;
	}
	if (glfwGetKey(window, GLFW_KEY_S)) {
		position -= forward * moveSpeed * deltaTime;
	}
	if (glfwGetKey(window, GLFW_KEY_D)) {
		position += right * moveSpeed * deltaTime;
	}
	if (glfwGetKey(window, GLFW_KEY_SPACE)) {
		position += up * moveSpeed * deltaTime;
	}
	if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL)) {
		position -= up * moveSpeed * deltaTime;
	}

	//move angle
	if (glfwGetMouseButton(window, 1)) {
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
		glm::vec2 mouseDelta = Application::get()->GetMouseDelta();
		theta += turnSpeed * mouseDelta.x;
		phi -= turnSpeed * mouseDelta.y;
	}
	else {
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
	}
}

glm::mat4 Camera::GetViewMatrix()
{
	float thertaRad = glm::radians(theta);
	float phiRad = glm::radians(phi);
	glm::vec3 forward(cos(phiRad) * cos(thertaRad), sin(phiRad), cos(phiRad * sin(thertaRad)));

	return glm::lookAt(position, position + forward, glm::vec3(0, 1, 0));
}

glm::mat4 Camera::GetProjectionMatrix(float width, float height)
{
	return glm::perspective(fieldOfView, width / height, nearClipPlane, farClipPlane);
}
