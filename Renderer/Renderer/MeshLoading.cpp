#include "MeshLoading.h"

MeshLoading::MeshLoading() {
	Mesh* newMesh = new Mesh();
	newMesh->InitialiseFromFile("characters\\Pyro\\pyro.fbx");
	meshes.push_back(newMesh);
}

void MeshLoading::Update(){

}
void MeshLoading::Draw() {
	for (Mesh* m : meshes) {
		m->Draw();
	}
}