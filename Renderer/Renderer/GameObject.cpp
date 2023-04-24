#include "GameObject.h"
#include "Mesh.h"
#include "ShaderProgram.h"
#include "Camera.h"
#include "Scene.h"
#include "Light.h"

GameObject::GameObject(glm::mat4 transform, Mesh* mesh, ShaderProgram* shaderProgram)
{
	this->transform = transform;
	this->mesh = mesh;
	shader = shaderProgram;
	scale = { mesh->quadTransform[0].x, mesh->quadTransform[1].y, mesh->quadTransform[2].z };
	position = { mesh->quadTransform[0].w, mesh->quadTransform[1].w, mesh->quadTransform[2].w };
}

void GameObject::SetTransform(glm::vec3 position, glm::vec3 eulerAngles, glm::vec3 scale)
{
	this->position = position;
	this->rotation = eulerAngles;
	this->scale = scale;

	transform = glm::translate(glm::mat4(1), position)
		* glm::rotate(glm::mat4(1), glm::radians(eulerAngles.z), glm::vec3(0, 0, 1))
		* glm::rotate(glm::mat4(1), glm::radians(eulerAngles.y), glm::vec3(0, 1, 0))
		* glm::rotate(glm::mat4(1), glm::radians(eulerAngles.x), glm::vec3(1, 0, 0))
		* glm::scale(glm::mat4(1), scale);
}

void GameObject::SetPosition(glm::vec3 position)
{
	this->position = position;
	transform = glm::translate(glm::mat4(1), position)
		* glm::rotate(glm::mat4(1), glm::radians(rotation.z), glm::vec3(0, 0, 1))
		* glm::rotate(glm::mat4(1), glm::radians(rotation.y), glm::vec3(0, 1, 0))
		* glm::rotate(glm::mat4(1), glm::radians(rotation.x), glm::vec3(1, 0, 0))
		* glm::scale(glm::mat4(1), scale);
}

void GameObject::SetRotationEuler(glm::vec3 eulerAngles)
{
	rotation = eulerAngles;
	transform = glm::translate(glm::mat4(1), position)
		* glm::rotate(glm::mat4(1), glm::radians(eulerAngles.z), glm::vec3(0, 0, 1))
		* glm::rotate(glm::mat4(1), glm::radians(eulerAngles.y), glm::vec3(0, 1, 0))
		* glm::rotate(glm::mat4(1), glm::radians(eulerAngles.x), glm::vec3(1, 0, 0))
		* glm::scale(glm::mat4(1), scale);
}

void GameObject::SetScale(glm::vec3 scale)
{
	this->scale = scale;
	transform = glm::translate(glm::mat4(1), position)
		* glm::rotate(glm::mat4(1), glm::radians(rotation.z), glm::vec3(0, 0, 1))
		* glm::rotate(glm::mat4(1), glm::radians(rotation.y), glm::vec3(0, 1, 0))
		* glm::rotate(glm::mat4(1), glm::radians(rotation.x), glm::vec3(1, 0, 0))
		* glm::scale(glm::mat4(1), scale);
}

void GameObject::Draw(Scene* scene)
{
	//enable shader
	shader->Enable();
	//bind position
	auto pvm = scene->GetCamera()->GetProjectionMatrix(scene->GetWindowSize().x, scene->GetWindowSize().y) * scene->GetCamera()->GetViewMatrix() * transform;
	shader->bindUniform("ProjectionMatrix", pvm);

	//bind model
	shader->bindUniform("ModelMatrix", transform);
	//bind lighting
	shader->bindUniform("AmbientColour", scene->GetAmbientLight());
	shader->bindUniform("LightColour", scene->GetDirectionalLight()->GetColour());
	shader->bindUniform("LightDirection", scene->GetDirectionalLight()->GetDirection());
	//bind camera position
	shader->bindUniform("CameraPosition", scene->GetCamera()->GetPosition());

	int numLights = scene->GetNumLights();
	shader->bindUniform("numLights", numLights);
	shader->bindUniform("PointLightPosition", numLights, scene->GetPointLightPositions());
	shader->bindUniform("PointLightColour", numLights, scene->GetPointLightColours());

	mesh->ApplyMaterial(this->shader);
	mesh->Draw();
}
