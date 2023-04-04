#include "MeshLoading.h"
#include "Camera.h"
#include "Scene.h"
#include "Light.h"

MeshLoading::MeshLoading() {

	//scene setup
	Light* light = new Light({ 1,1,1 }, { 0.8f ,1 ,0.8f });
	glm::vec3 ambientLight = { 0.75f,0.75f,0.75f };
	scene = new Scene(camera, glm::vec2(GetWindowWidth(), GetWindowHeight()), light, ambientLight);

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

	for (int i = 0; i < 10; i++) {
		GameObject* soulSpearInstance = new GameObject(soulSpear->quadTransform, soulSpear, &this->shader);
		soulSpearInstance->SetTransform({ i * i, 0, 0 }, { 0, i * 20, 0 }, { i * 1.01f,i * 1.01f, i * 1.01f });
		scene->AddGameObject(soulSpearInstance);
	}

	//camera setup
	camera->SetPosition(glm::vec3(0, 5, 10));
	camera->SetRotation(-90, -10);
	camera->SetMoveSpeed(50);

	//light setup
	scene->GetLight()->SetColour({ 1 ,1 ,1 });
	scene->SetAmbientLight({ 1, 1, 1 });
}

MeshLoading::~MeshLoading()
{
	delete scene;
}

void MeshLoading::Update() {
	float time = glfwGetTime();
	scene->GetLight()->SetDirection(glm::normalize(glm::vec3((float)sin(time), 0, (float)cos(time))));
}
void MeshLoading::Draw() {
	scene->Draw();
}