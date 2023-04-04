#pragma once
#include "Graphics.h"
class Light {
public:
	Light(glm::vec3 direction, glm::vec3 colour);
	glm::vec3 GetDirection() { return direction; };
	glm::vec3 GetColour() { return colour; };
	void SetDirection(glm::vec3 direction);
	void SetColour(glm::vec3 colour);
protected:
	glm::vec3 direction;
	glm::vec3 colour;
};