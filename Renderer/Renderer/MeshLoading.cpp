#include "MeshLoading.h"
#include "Camera.h"
#include "Scene.h"
#include "Light.h"
#include "IMGUI_include.h"
#include <iostream>
#include "Animation.h"
#include "Animator.h"

MeshLoading::MeshLoading() {

	//initialise imgui
	ImGui::CreateContext();
	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init();


	//scene setup
	Light* light = new Light({ 1,1,1 }, { 0 ,0,0 }, 0);
	glm::vec3 ambientLight = { 0.75f,0.75f,0.75f };
	scene = new Scene(camera, glm::vec2(GetWindowWidth(), GetWindowHeight()), light, ambientLight);

#pragma region SpecularMeshes

	////setup meshes

	//Mesh* pyro = new Mesh();
	//pyro->SetPBR(false);
	//pyro->InitialiseFromFile("characters\\Pyro\\pyro.fbx");
	//pyro->LoadSpecularMaterial("characters\\Pyro\\pyro.mtl");
	//GameObject* pyroInstance = new GameObject(pyro->quadTransform, pyro, &this->phongShader);
	//pyroInstance->SetPosition({ 750, 0, 750 });
	//scene->AddGameObject(pyroInstance);

	//Mesh* marksman = new Mesh();
	//marksman->SetPBR(false);
	//marksman->InitialiseFromFile("characters\\Marksman\\Marksman.fbx");
	//marksman->LoadSpecularMaterial("characters\\Marksman\\marksman.mtl");
	//GameObject* marksmanInstance = new GameObject(marksman->quadTransform, marksman, &this->phongShader);
	//marksmanInstance->SetPosition({ -750,0,-750 });
	//scene->AddGameObject(marksmanInstance);

	//Mesh* tank = new Mesh();
	//tank->SetPBR(false);
	//tank->InitialiseFromFile("characters\\enemynormal\\EnemyNormal.fbx");
	//tank->LoadSpecularMaterial("characters\\enemynormal\\enemyNormal.mtl");
	//GameObject* tankInstance = new GameObject(tank->quadTransform, tank, &this->phongShader);
	//tankInstance->SetPosition({ -750,0,750 });
	//scene->AddGameObject(tankInstance);

	//Mesh* demolition = new Mesh();
	//demolition->SetPBR(false);
	//demolition->InitialiseFromFile("characters\\Demolition\\demolition.fbx");
	//demolition->LoadSpecularMaterial("characters\\Demolition\\demolition.mtl");
	//GameObject* demolitionInstance = new GameObject(demolition->quadTransform, demolition, &this->phongShader);
	//demolitionInstance->SetPosition({ 750,0,-750 });
	//scene->AddGameObject(demolitionInstance);

#pragma endregion

#pragma region PBRMeshes

	Model* spider = new Model();
	spider->shaderType == Model::ShaderType::PBRMask;
	spider->InitialiseModelFromFile("Meshes\\PBR\\Spider\\Animations\\MESH_CHA_BigSpider.fbx", true);
	GameObject* spiderInstance = new GameObject(spider->GetMeshes()[0]->quadTransform, spider, &this->PBRShader);
	spiderInstance->SetPosition({ 0, 0, 0 });
	spiderInstance->SetScale(glm::vec3(1, 1, 1));
	scene->AddGameObject(spiderInstance);
	spiderInstance->name = "Spider";

	//Model* mite = new Model();
	//mite->shaderType == Model::ShaderType::PBRMask;
	//mite->InitialiseModelFromFile("Meshes\\PBR\\Mite\\Animations\\MESH_CHA_Mite.fbx");
	//GameObject* miteInstance = new GameObject(mite->GetMeshes()[0]->quadTransform, mite, &this->PBRShader);
	//miteInstance->SetPosition({ 0, 0, 0 });
	//miteInstance->SetScale(glm::vec3(1, 1, 1));
	//scene->AddGameObject(miteInstance);
	//miteInstance->name = "Mite";

	/*Model* slug = new Model();
	slug->shaderType == Model::ShaderType::PBRMask;
	slug->InitialiseModelFromFile("Meshes\\PBR\\Slug\\Animations\\MESH_CHA_Worm.fbx", true);
	GameObject* slugInstance = new GameObject(slug->GetMeshes()[0]->quadTransform, slug, &this->PBRShader);
	slugInstance->SetPosition({ 0, 0, 0 });
	slugInstance->SetScale(glm::vec3(1, 1, 1));
	scene->AddGameObject(slugInstance);
	slugInstance->name = "Slug";*/


	//Model* wasp = new Model();
	//wasp->shaderType == Model::ShaderType::PBRMask;
	//wasp->InitialiseModelFromFile("Meshes\\PBR\\Wasp\\Animations\\MESH_CHA_Wasp.fbx");
	//GameObject* waspInstance = new GameObject(wasp->GetMeshes()[0]->quadTransform, wasp, &this->PBRShader);
	//waspInstance->SetPosition({ 0, 0, 0 });
	//waspInstance->SetScale(glm::vec3(1, 1, 1));
	//scene->AddGameObject(waspInstance);
	//waspInstance->name = "Wasp";

	SetCurrentGameObject(spiderInstance);

#pragma endregion


#pragma region SoulSpears

	//soul spears with rotation and scale

	/*Mesh* soulSpear = new Mesh();
	soulSpear->InitialiseFromFile("soulspear\\soulspear.obj");
	soulSpear->LoadSpecularMaterial("soulspear\\soulspear.mtl");

	for (int i = 0; i < 10; i++) {
		GameObject* soulSpearInstance = new GameObject(soulSpear->quadTransform, soulSpear, &this->phongShader);
		soulSpearInstance->SetTransform({ i * i * 10, 0, 0 }, { 0, i * 20, 0 }, { i * 10.0f,i * 10.0f, i * 10.0f });
		scene->AddGameObject(soulSpearInstance);
	}*/
#pragma endregion

	//camera setup
	camera->SetPosition(glm::vec3(0, 500, 1000));
	camera->SetRotation(-90, -10);
	//camera->SetMoveSpeed(50);

	//light setup
	scene->GetDirectionalLight()->SetColour({ 1 ,1 ,1 }, 1);
	scene->SetAmbientLight({ 0.75f, 0.75f, 0.75f });

	Light* redLight = new Light({ 600,300,0 }, { 1,0,0 }, 50000000);
	Light* blueLight = new Light({ -650,100, 0 }, { 1,0,1 }, 50000000);

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
		scene->GetPointLights()[0]->SetColour(tempColour, 500000000);
	}

	auto tempPos2 = scene->GetPointLights()[1]->GetDirection();
	if (ImGui::DragFloat3("Light 2 Position (XYZ)", &tempPos2[0])) {
		scene->GetPointLights()[1]->SetDirection(tempPos2);
	}
	auto tempColour2 = scene->GetPointLights()[1]->GetRawColour();
	if (ImGui::DragFloat3("Light 2 Colour", &tempColour2[0], 0.01f, 0, 1, "%.2f", 1.0f)) {
		scene->GetPointLights()[1]->SetColour(tempColour2, 500000000);
	}

	auto directionalLightSpeedMultiplier = directionalLightSpeed;
	if (ImGui::DragFloat("Directional Light Speed", &directionalLightSpeedMultiplier, 0.01f, 0, 10, "%.2f", 1.0f)) {
		directionalLightSpeed = directionalLightSpeedMultiplier;
		scene->GetDirectionalLight()->SetDirection(glm::normalize(glm::vec3((float)sin(directionalLightSpeed), 0.5f, (float)cos(directionalLightSpeed))));

	}
	auto directionalLightIntense = directionalLightIntensity;
	if (ImGui::DragFloat("Directional Light Intensity", &directionalLightIntense, 1.0f, 0, 1000, "%.2f", 1.0f)) {
		directionalLightIntensity = directionalLightIntense;
		scene->GetDirectionalLight()->SetColour(scene->GetDirectionalLight()->GetRawColour(), directionalLightIntensity);
	}
	auto directionalLightColour = scene->GetDirectionalLight()->GetRawColour();
	if (ImGui::DragFloat3("Directional Light Colour", &directionalLightColour[0], 0.01f, 0, 1, "%.2f", 1.0f)) {
		scene->GetDirectionalLight()->SetColour(directionalLightColour, directionalLightIntensity);
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

	//enable disable depth test
	if (ImGui::Button("Light Set Up 1")) {
		scene->GetPointLights()[0]->SetColour({ 1,1,1 }, 500000000);
		scene->GetPointLights()[0]->SetDirection({ 1000,1000,1000 });
		scene->GetPointLights()[1]->SetColour({ 0,0,0.5f }, 500000000);
		scene->GetPointLights()[1]->SetDirection({ -1000,-1000,-1000 });
		scene->GetDirectionalLight()->SetDirection(glm::normalize(glm::vec3((float)sin(1), 0.75f, (float)cos(0))));
	}

	currentSelectedGameObject->DrawIMGUI();


	//render imgui
	ImGui::Render();

	//update directional light direction
	//float time = glfwGetTime();
	//scene->GetDirectionalLight()->SetDirection(glm::normalize(glm::vec3((float)sin(directionalLightSpeed), 0.5f, (float)cos(directionalLightSpeed))));
	for (int i = 0; i < scene->GameObjectCount(); i++)
	{
		scene->GetGameObject(i)->Update(GetDeltaTime());
	}
}
void MeshLoading::Draw() {
	//draw scene
	scene->Draw();
	//draw imgui
	if (ImGui::GetDrawData()) {
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	}
}