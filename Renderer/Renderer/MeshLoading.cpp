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

	/*Mesh* spider = new Mesh();
	spider->SetPBR(true);
	spider->InitialiseFromFile("PBR\\Spider\\Animations\\MESH_CHA_BigSpider.fbx");
	spider->LoadPBRMaskMaterial("PBR\\Spider\\Materials\\SpiderMaterial.mat");
	GameObject* spiderInstance = new GameObject(spider->quadTransform, spider, &this->PBRShader);
	spiderInstance->SetPosition({ 1000, 0, 1000 });
	spiderInstance->SetScale(glm::vec3(1000, 1000, 1000));
	spiderInstance->SetRotationEuler(glm::vec3(-90, 0, 0));
	scene->AddGameObject(spiderInstance);*/

	//Mesh* mite = new Mesh();
	//mite->SetPBR(true);
	//mite->InitialiseFromFile("Meshes\\PBR\\Mite\\Animations\\MESH_CHA_Mite.fbx");
	//mite->LoadPBRMaskMaterial("Textures\\Mite\\MiteMaterial.mat");
	//GameObject* miteInstance = new GameObject(mite->quadTransform, mite, &this->PBRShader);
	//miteInstance->SetPosition({ -1000, 0, -1000 });
	//miteInstance->SetScale(glm::vec3(10, 10, 10));
	//scene->AddGameObject(miteInstance);
	//miteInstance->name = "Mite";


	Mesh* slug = new Mesh();
	slug->SetPBR(true);
	slug->InitialiseFromFile("Meshes\\PBR\\Slug\\Animations\\MESH_CHA_Worm.fbx");
	slug->LoadPBRMaskMaterial("Textures\\Slug\\SlugMaterial.mat");
	GameObject* slugInstance = new GameObject(slug->quadTransform, slug, &this->PBRShader);
	slugInstance->SetPosition({ 1000, 0, -1000 });
	slugInstance->SetScale(glm::vec3(10, 10, 10));
	scene->AddGameObject(slugInstance);
	slugInstance->name = "Slug";

	//Mesh* wasp = new Mesh();
	//wasp->SetPBR(true);
	//wasp->InitialiseFromFile("Meshes\\PBR\\Wasp\\Animations\\MESH_CHA_Wasp.fbx");
	//wasp->LoadPBRMaskMaterial("Textures\\Wasp\\WaspMaterial.mat");
	//GameObject* waspInstance = new GameObject(wasp->quadTransform, wasp, &this->PBRShader);
	//waspInstance->SetPosition({ -1000, 0, 1000 });
	//waspInstance->SetScale(glm::vec3(1000, 1000, 1000));
	//waspInstance->SetRotationEuler(glm::vec3(-90, 0, 0));
	//scene->AddGameObject(waspInstance);



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

	for (int i = 0; i < scene->GetGameObjects().size(); i++)
	{
		scene->GetGameObject(i)->DrawIMGUI();
	}

	//render imgui
	ImGui::Render();

	//update directional light direction
	//float time = glfwGetTime();
	//scene->GetDirectionalLight()->SetDirection(glm::normalize(glm::vec3((float)sin(directionalLightSpeed), 0.5f, (float)cos(directionalLightSpeed))));
	/*for (int i = 0; i < scene->GameObjectCount(); i++)
	{
		scene->GetGameObject(i)->SetPosition(glm::vec3(sin(time) * i * 1000, 0, i * 1000));
		scene->GetGameObject(i)->SetRotationEuler(glm::vec3(0,time * 50,0));
	}*/
}
void MeshLoading::Draw() {
	//draw scene
	scene->Draw();
	//draw imgui
	if (ImGui::GetDrawData()) {
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	}
}