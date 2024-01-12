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
	for (GameObject* i : gameObjects) {
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

	if (currentGameObject != nullptr) {
		ImGui::Text(("Current Selected Object: " + currentGameObject->name).c_str());
	}
	else {
		ImGui::Text("Current Selected Object: None");
	}

	//Actually Write It Out You Fuckwit
	for (int i = 0; i < gameObjects.size(); i++)
	{
		if (gameObjects[i]->GetParent() == nullptr) {
			gameObjects[i]->DrawIMGUI(this);
		}
	}

	//at end reset dirty flags for scene heirarchy

	for (int i = 0; i < gameObjects.size(); i++)
	{
		gameObjects[i]->SetDirtyUI(true);
	}

	ImGui::PopID();
	ImGui::End();
}

void Scene::DrawCurrentSelectedObject()
{
	ImGui::Begin("Current Selected Object");
	ImGui::PushID("Current Selected Object");

	if (currentGameObject != nullptr) {
		ImGui::Text(("Selected Object: " + currentGameObject->name).c_str());
		currentGameObject->DrawIMGUIWindow();
	}
	else {
		ImGui::Text("Selected Object: _NULL_");
	}

	ImGui::PopID();
	ImGui::End();
}
