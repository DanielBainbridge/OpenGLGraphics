#include "MeshLoading.h"
#include "Camera.h"
#include "Scene.h"
#include "Light.h"
#include "IMGUI_include.h"
#include <iostream>

MeshLoading::MeshLoading() {

	//initialise imgui
	ImGui::CreateContext();
	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init();


	//scene setup
	Light* light = new Light({ 1,1,1 }, { 0 ,0,0 }, 0);
	glm::vec3 ambientLight = { 0.75f,0.75f,0.75f };
	scene = new Scene(camera, glm::vec2(GetWindowWidth(), GetWindowHeight()), light, ambientLight);

	//setup meshes

	Mesh* pyro = new Mesh();
	pyro->InitialiseFromFile("characters\\Pyro\\pyro.fbx");
	pyro->LoadMaterial("characters\\Pyro\\pyro.mtl");
	GameObject* pyroInstance = new GameObject(pyro->quadTransform, pyro, &this->shader);
	pyroInstance->SetPosition({ 750, 0, 750 });
	scene->AddGameObject(pyroInstance);

	Mesh* marksman = new Mesh();
	marksman->InitialiseFromFile("characters\\Marksman\\Marksman.fbx");
	marksman->LoadMaterial("characters\\Marksman\\marksman.mtl");
	GameObject* marksmanInstance = new GameObject(marksman->quadTransform, marksman, &this->shader);
	marksmanInstance->SetPosition({ -750,0,-750 });
	scene->AddGameObject(marksmanInstance);

	Mesh* tank = new Mesh();
	tank->InitialiseFromFile("characters\\enemynormal\\EnemyNormal.fbx");
	tank->LoadMaterial("characters\\enemynormal\\enemyNormal.mtl");
	GameObject* tankInstance = new GameObject(tank->quadTransform, tank, &this->shader);
	tankInstance->SetPosition({ -750,0,750 });
	scene->AddGameObject(tankInstance);

	Mesh* demolition = new Mesh();
	demolition->InitialiseFromFile("characters\\Demolition\\demolition.fbx");
	demolition->LoadMaterial("characters\\Demolition\\demolition.mtl");
	GameObject* demolitionInstance = new GameObject(demolition->quadTransform, demolition, &this->shader);
	demolitionInstance->SetPosition({ 750,0,-750 });
	scene->AddGameObject(demolitionInstance);


	//soul spears with rotation and scale

	Mesh* soulSpear = new Mesh();
	soulSpear->InitialiseFromFile("soulspear\\soulspear.obj");
	soulSpear->LoadMaterial("soulspear\\soulspear.mtl");

	for (int i = 0; i < 10; i++) {
		GameObject* soulSpearInstance = new GameObject(soulSpear->quadTransform, soulSpear, &this->shader);
		soulSpearInstance->SetTransform({ i * i * 10, 0, 0 }, { 0, i * 20, 0 }, { i * 10.0f,i * 10.0f, i * 10.0f });
		scene->AddGameObject(soulSpearInstance);
	}

	//camera setup
	camera->SetPosition(glm::vec3(0, 500, 1000));
	camera->SetRotation(-90, -10);
	//camera->SetMoveSpeed(50);

	//light setup
	scene->GetDirectionalLight()->SetColour({ 1 ,1 ,1 }, 1);
	scene->SetAmbientLight({ 0.75f, 0.75f, 0.75f });

	Light* redLight = new Light({ 600,300,0 }, { 1,0,0 }, 500000);
	Light* blueLight = new Light({ -650,100, 0 }, { 1,0,1 }, 500000);

	scene->AddPointLight(redLight);
	scene->AddPointLight(blueLight);
}

MeshLoading::~MeshLoading()
{
	delete scene;
}

void MeshLoading::Update() {
	//start imgui frame
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();

	//do imgui buttons

	auto tempPos = scene->GetPointLights()[0]->GetDirection();
	if (ImGui::DragFloat3("Light 1 Position (XYZ)", &tempPos[0])) {
		scene->GetPointLights()[0]->SetDirection(tempPos);
	}
	auto tempColour = scene->GetPointLights()[0]->GetRawColour();
	if (ImGui::DragFloat3("Light 1 Colour", &tempColour[0], 0.01f, 0, 1, "%.2f", 1.0f)) {
		scene->GetPointLights()[0]->SetColour(tempColour, 500000);
	}
	
	auto tempPos2 = scene->GetPointLights()[1]->GetDirection();
	if (ImGui::DragFloat3("Light 2 Position (XYZ)", &tempPos2[0])) {
		scene->GetPointLights()[1]->SetDirection(tempPos2);
	}
	auto tempColour2 = scene->GetPointLights()[1]->GetRawColour();
	if (ImGui::DragFloat3("Light 2 Colour", &tempColour2[0], 0.01f, 0, 1, "%.2f", 1.0f)) {
		scene->GetPointLights()[1]->SetColour(tempColour2, 500000);
	}
	//enable disable depth test
	if (ImGui::Button("Depth Test On/Off")) {
		if (depthTestEnable) {
			glDisable(GL_DEPTH_TEST);
			depthTestEnable = false;
		}
		else {
			glEnable(GL_DEPTH_TEST);
			depthTestEnable = true;
		}
	}

	//render imgui
	ImGui::Render();

	//update directional light direction
	float time = glfwGetTime();
	scene->GetDirectionalLight()->SetDirection(glm::normalize(glm::vec3((float)sin(time), 0, (float)cos(time))));

}
void MeshLoading::Draw() {
	//draw scene
	scene->Draw();
	//draw imgui
	if (ImGui::GetDrawData()) {
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	}
}