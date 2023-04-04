#pragma once
#include "Graphics.h"
#define MAX_LIGHTS 4

//forward declaration
class Camera;
class GameObject;
class Light;

class Scene {
public:
	Scene();
	Scene(Camera* camera, glm::vec2 windowSize, Light* light, glm::vec3 ambientLight);
	~Scene();
	void Draw();
	void AddGameObject(GameObject* instance);
	Camera* GetCamera() { return camera; };
	glm::vec2 GetWindowSize() { return windowSize; };
	Light* GetDirectionalLight() { return directionalLight; };
	glm::vec3 GetAmbientLight() { return ambientLight; };
	int GetNumLights() { return pointLights.size(); };
	glm::vec3* GetPointLightPositions() { return &pointLightPositions[0]; };
	glm::vec3* GetPointLightColours() { return &pointLightColours[0]; };
	std::vector<Light*> GetPointLights() { return pointLights; };

	void SetAmbientLight(glm::vec3 light) { ambientLight = light; };
	

protected:
	Camera* camera;
	glm::vec2 windowSize;
	Light* directionalLight;
	std::vector<Light*> pointLights;
	glm::vec3 pointLightPositions[MAX_LIGHTS];
	glm::vec3 pointLightColours[MAX_LIGHTS];

	glm::vec3 ambientLight;
	std::vector<GameObject*> gameObjects;
};