#pragma once
#include "Application.h"
#include "Mesh.h"
class MeshLoading : public Application {
public:
	MeshLoading();
	virtual void Update() override;
	virtual void Draw() override;
private:
	std::vector<Mesh*> meshes;
};