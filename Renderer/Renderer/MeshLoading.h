#pragma once
#include "Application.h"
#include "Mesh.h"
#include "Texture.h"
#include "GameObject.h"
class Scene;
class MeshLoading : public Application {
public:
	MeshLoading();
	void SetCurrentGameObject(GameObject* gO) { currentSelectedGameObject = gO; };
	~MeshLoading();
	virtual void Update() override;
	virtual void Draw() override;
private:
	Scene* scene;
	bool depthTestEnable = true;
	float directionalLightSpeed = 1;
	float directionalLightIntensity = 1;
	GameObject* currentSelectedGameObject = nullptr;
};