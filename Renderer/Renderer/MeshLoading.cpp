#include "MeshLoading.h"
#include "Camera.h"

MeshLoading::MeshLoading() {
	//setup meshes
	/*Mesh* newMesh = new Mesh();
	newMesh->InitialiseFromFile("characters\\Pyro\\pyro.fbx");
	newMesh->LoadMaterial("characters\\Pyro\\Pyro_S.tga");
	newMesh->quadTransform = { 1,0,0,0,
		0,1,0,0,
		0,0,1,0,
		750,0,0,1 };
	meshes.push_back(newMesh);

	Mesh* newNewMesh = new Mesh();
	newNewMesh->InitialiseFromFile("characters\\Marksman\\Marksman.fbx");
	newNewMesh->LoadMaterial("characters\\Marksman\\Marksman_S.tga");

	newNewMesh->quadTransform = { 1,0,0,0,
		0,1,0,0,
		0,0,1,0,
		750,0,1500,1 };
	meshes.push_back(newNewMesh);

	Mesh* newNewNewMesh = new Mesh();
	newNewNewMesh->InitialiseFromFile("characters\\Enemytank\\EnemyTank.fbx");
	newNewNewMesh->LoadMaterial("characters\\Enemytank\\EnemyTank_S.tga");

	newNewNewMesh->quadTransform = { 1,0,0,0,
		0,1,0,0,
		0,0,1,0,
		-750,0,1500,1 };
	meshes.push_back(newNewNewMesh);

	Mesh* newNewNewNewMesh = new Mesh();
	newNewNewNewMesh->InitialiseFromFile("characters\\Demolition\\demolition.fbx");
	newNewNewNewMesh->LoadMaterial("characters\\Demolition\\demolition_s.tga");

	newNewNewNewMesh->quadTransform = { 1,0,0,0,
		0,1,0,0,
		0,0,1,0,
		-750,0,0,1 };
	meshes.push_back(newNewNewNewMesh);*/
	

	/*Mesh* stanBun = new Mesh();
	stanBun->InitialiseFromFile("stanford\\Bunny.obj");
	stanBun->LoadMaterial("stanford\\Bunny.mtl");
	stanBun->SetPosition(glm::vec3(-10, 0, 10));
	meshes.push_back(stanBun);

	Mesh* stanBud = new Mesh();
	stanBud->InitialiseFromFile("stanford\\Buddha.obj");
	stanBud->LoadMaterial("stanford\\Buddha.mtl");
	stanBud->SetPosition(glm::vec3(-10, 0, -10));
	meshes.push_back(stanBud);

	Mesh* stanLuc = new Mesh();
	stanLuc->InitialiseFromFile("stanford\\Lucy.obj");
	stanLuc->LoadMaterial("stanford\\Lucy.mtl");
	stanLuc->SetPosition(glm::vec3(10, 0, -10));
	meshes.push_back(stanLuc);

	Mesh* stanDrag = new Mesh();
	stanDrag->InitialiseFromFile("stanford\\Dragon.obj");
	stanDrag->LoadMaterial("stanford\\Dragon.mtl");
	stanDrag->SetPosition(glm::vec3(10, 0, 10));
	meshes.push_back(stanDrag);*/

	Mesh* soulSpear = new Mesh();
	soulSpear->InitialiseFromFile("soulspear\\soulspear.obj");
	soulSpear->LoadMaterial("soulspear\\soulspear.mtl");
	meshes.push_back(soulSpear);



	//camera setup
	camera->SetPosition(glm::vec3(0, 5, 10));
	camera->SetRotation(-90, -10);
	camera->SetMoveSpeed(5);

	//light setup
	light.colour = { 1 ,1 ,1 };
	ambientLight = { 1 ,1 ,1 };
	light.direction = {-1,-1,-1};
}

void MeshLoading::Update() {
	float time = glfwGetTime();
	light.direction = glm::normalize(glm::vec3(sin(time), 0, cos(time)));
}
void MeshLoading::Draw() {
	for (Mesh* m : meshes) {

		shader.bindUniform("AmbientColour", ambientLight);
		shader.bindUniform("LightColour", light.colour);
		shader.bindUniform("LightDirection", light.direction);
		shader.bindUniform("ProjectionMatrix", camera->GetProjectionMatrix(windowWidth, windowHeight) * camera->GetViewMatrix() * m->quadTransform);
		shader.bindUniform("ModelMatrix", m->quadTransform);
		shader.bindUniform("CameraPosition", camera->GetPosition());
		m->ApplyMaterial(&shader);
		m->Draw();
	}

}