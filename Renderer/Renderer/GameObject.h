#pragma once
#include "Graphics.h"
#include "Application.h"
class Mesh;
class ShaderProgram;
class Scene;
class GameObject {
public:
	GameObject() {};
	GameObject(glm::mat4 transform, Mesh* mesh, ShaderProgram* shaderProgram);
	void SetTransform(glm::vec3 position, glm::vec3 eulerAngles, glm::vec3 scale);
	void SetPosition(glm::vec3 position);
	void SetRotationEuler(glm::vec3 eulerAngles);
	void SetScale(glm::vec3 scale);
	void Draw(Scene* scene);
	ShaderProgram* shader;
protected:
	glm::mat4 transform;
	Mesh* mesh;
	glm::vec3 position, rotation, scale;
};