#pragma once
#include "Graphics.h"
class Camera {
public:
	Camera();
	Camera(float fieldOfView, float nearClipPlane, float farClipPlane);
	void UpdateCamera(float deltaTime, GLFWwindow* window);
	glm::mat4 GetViewMatrix();
	glm::mat4 GetProjectionMatrix(float width, float height);
	float GetTurnSpeed() { return turnSpeed; }
	float GetMoveSpeed() { return moveSpeed; }
	inline void SetNearClip(float value) { nearClipPlane = value; };
	inline void SetFarClip(float value) {farClipPlane = value;};
	inline void SetFieldOfView(float value) {fieldOfView = value;};
	inline void SetTurnSpeed(float value) { turnSpeed = value; };
	inline void SetMoveSpeed(float value) { moveSpeed = value; };
	inline void SetPosition(glm::vec3 value) { position = value; };
	inline glm::vec3 GetPosition() { return position; };
	inline void SetRotation(float thetaVal, float phiVal) { theta = thetaVal; phi = phiVal; };

private:
	float turnSpeed = 0.1f;
	float moveSpeed = 500;
	float fieldOfView;
	float nearClipPlane;
	float farClipPlane;
	float theta = 0;
	float phi = 0;
	glm::vec3 position;
};