#include "Scene.h"
#include "Camera.h"
#include "GameObject.h"
#include "Application.h"
#include "Light.h"
#include "IMGUI_include.h"

Scene::Scene(Camera* camera, glm::vec2 windowSize, Light* light, glm::vec3 ambientLight)
{
	this->camera = camera;
	this->windowSize = windowSize;
	this->directionalLight = light;
	this->ambientLight = ambientLight;
}

Scene::~Scene()
{
	for (auto it = gameObjects.begin(); it != gameObjects.end(); it++) {
		delete* it;
	}
}

void Scene::Draw()
{
	for (int i = 0; i < MAX_LIGHTS && i < pointLights.size(); i++)
	{
		pointLightPositions[i] = pointLights[i]->GetDirection();
		pointLightColours[i] = pointLights[i]->GetColour();
	}
	for (GameObject* i: gameObjects) {
		i->Draw(this);
	}
}

void Scene::AddGameObject(GameObject* instance)
{
	gameObjects.push_back(instance);
}

GameObject* Scene::GetGameObject(int location)
{
	if (location > gameObjects.size() || gameObjects.size() == 0) {
		return nullptr;
	}
	return gameObjects[location];
}

void Scene::AddPointLight(Light* light)
{
	pointLights.push_back(light);
}

void Scene::DrawIMGUI()
{
	ImGui::Begin("Scene Heirarchy");
	ImGui::PushID("Scene Heirarchy");

	//Actually Write It Out You Fuckwit

	


	ImGui::PopID();
	ImGui::End();
}
