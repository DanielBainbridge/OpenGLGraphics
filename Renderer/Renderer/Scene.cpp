#include "Scene.h"
#include "Camera.h"
#include "GameObject.h"
#include "Application.h"
#include "Light.h"

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
