#include "Light.h"

Light::Light(glm::vec3 direction, glm::vec3 colour)
{
	this->direction = direction;
	this->colour = colour;
}

void Light::SetDirection(glm::vec3 direction)
{
	this->direction = direction;
}

void Light::SetColour(glm::vec3 colour)
{
	this->colour = colour;
}
