#pragma once
#include "Application.h"
#include "Mesh.h"
#include "Model.h"
#include "Texture.h"
#include "GameObject.h"
#include "TextureManager.h"
#include "MeshManager.h"
class Scene;
class MeshLoading : public Application {
public:
	MeshLoading();
	void SetCurrentGameObject(GameObject* gO) { currentSelectedGameObject = gO; };
	~MeshLoading();
	virtual void Update() override;
	virtual void Draw() override;
	virtual void DrawIMGUI() override;
private:
	Scene* scene;
	bool depthTestEnable = true;
	float directionalLightSpeed = 1;
	float directionalLightIntensity = 1;
	GameObject* currentSelectedGameObject = nullptr;
	Managers::TextureManager* texManager;
	Managers::MeshManager* meshManager;
};