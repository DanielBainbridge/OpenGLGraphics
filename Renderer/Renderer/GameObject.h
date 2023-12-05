#pragma once
#include "Graphics.h"
#include "Application.h"
class Mesh;
class Model;
class ShaderProgram;
class Scene;
class GameObject {
public:
	GameObject() {};
	GameObject(glm::mat4 transform, Model* model, ShaderProgram* shaderProgram);
	void SetTransform(glm::vec3 position, glm::vec3 eulerAngles, glm::vec3 scale);
	void SetPosition(glm::vec3 position);
	void SetRotationEuler(glm::vec3 eulerAngles);
	void SetScale(glm::vec3 scale);
	void Draw(Scene* scene);
	void DrawIMGUI();
	std::string name;
	ShaderProgram* shader;
	Model* model = nullptr;
protected:
	glm::mat4 transform;
	glm::vec3 position, rotation, scale;
};