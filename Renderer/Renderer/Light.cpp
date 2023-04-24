#include "Light.h"

Light::Light(glm::vec3 direction, glm::vec3 colour, float intensity)
{
	this->direction = direction;
	rawColour = colour;
	this->colour = colour * intensity;
}

void Light::SetDirection(glm::vec3 direction)
{
	this->direction = direction;
}

void Light::SetColour(glm::vec3 colour, float intensity)
{
	rawColour = colour;
	this->colour = colour * intensity;
}
