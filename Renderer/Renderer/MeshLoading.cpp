#include "MeshLoading.h"
#include "Camera.h"
#include "Scene.h"
#include "Light.h"
#include "IMGUI_include.h"
#include <iostream>
#include "Animation.h"
#include "Animator.h"
#include "TextureManager.h"
#include "MeshManager.h"

MeshLoading::MeshLoading() {

	//initialise imgui
	ImGui::CreateContext();
	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init();


	//scene setup
	Light* light = new Light({ 1,1,1 }, { 0 ,0,0 }, 0);
	glm::vec3 ambientLight = { 0.75f,0.75f,0.75f };
	scene = new Scene(camera, glm::vec2(GetWindowWidth(), GetWindowHeight()), light, ambientLight);
	
	texManager = Managers::TextureManager::GetInstance();
	meshManager = Managers::MeshManager::GetInstance();

	meshManager->FindAllMeshes();
	texManager->FindAllTextures();


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

	//Model* spider = new Model();
	//spider->shaderType == Model::ShaderType::PBRMask;
	//spider->InitialiseModelFromFile("Meshes\\PBR\\Spider\\Animations\\MESH_CHA_BigSpider.fbx", true);
	//GameObject* spiderInstance = new GameObject(spider->GetMeshes()[0]->quadTransform, spider, &this->PBRShader);
	//spiderInstance->SetPosition({ 0, 0, 0 });
	//spiderInstance->SetScale(glm::vec3(1, 1, 1));
	//scene->AddGameObject(spiderInstance);
	//spiderInstance->name = "Spider";




		Model* slug = new Model();
		slug->shaderType == Model::ShaderType::PBRMask;
		slug->InitialiseModelFromFile("Meshes\\PBR\\Slug\\Animations\\MESH_CHA_Worm.fbx", true);
		GameObject* slugInstance = new GameObject(slug->GetMeshes()[0]->quadTransform, slug, &this->PBRShader);
		slugInstance->SetPosition({ 0, 0, 0 });
		slugInstance->SetScale(glm::vec3(1, 1, 1));
		scene->AddGameObject(slugInstance);
		slugInstance->name = "Slug " + std::to_string(0 + 1);
	
	//int miteCount = 1;
	//for (int j = 0; j < 2; j++) {
	//	for (int i = 0; i < 2; i++)
	//	{
	//		Model* mite = new Model();
	//		mite->shaderType == Model::ShaderType::PBRMask;
	//		mite->InitialiseModelFromFile("Meshes\\PBR\\Mite\\Animations\\MESH_CHA_Mite.fbx", true);
	//		GameObject* miteInstance = new GameObject(mite->GetMeshes()[0]->quadTransform, mite, &this->PBRShader);
	//		if (i != 0)
	//		{
	//			miteInstance->SetParent(scene->GetGameObject(scene->GetGameObjects().size() - 1));
	//		}
	//		miteInstance->SetPosition({ j, 0, i });
	//		miteInstance->SetScale(glm::vec3(1, 1, 1));
	//		scene->AddGameObject(miteInstance);
	//		miteInstance->name = "Mite" + std::to_string(miteCount);
	//		miteCount++;
	//	}
	//}




	/*Model* wasp = new Model();
	wasp->shaderType == Model::ShaderType::PBRMask;
	wasp->InitialiseModelFromFile("Meshes\\PBR\\Wasp\\Animations\\MESH_CHA_Wasp.fbx", true);
	GameObject* waspInstance = new GameObject(wasp->GetMeshes()[0]->quadTransform, wasp, &this->PBRShader);
	waspInstance->SetPosition({ 0, 0, 0 });
	waspInstance->SetScale(glm::vec3(1, 1, 1));
	scene->AddGameObject(waspInstance);
	waspInstance->name = "Wasp";*/


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
	camera->SetPosition(glm::vec3(0, 0, 10));
	camera->SetRotation(-90, 0);
	camera->SetMoveSpeed(10);

	//light setup
	scene->GetDirectionalLight()->SetColour({ 1 ,1 ,1 }, 1);
	scene->SetAmbientLight({ 0.75f, 0.75f, 0.75f });

	Light* redLight = new Light({ 600,300,0 }, { 1,0,0 }, 5000000);
	Light* blueLight = new Light({ -650,100, 0 }, { 1,0,1 }, 5000000);

	scene->AddPointLight(redLight);
	scene->AddPointLight(blueLight);
}

MeshLoading::~MeshLoading()
{
	delete scene;
}

void MeshLoading::Update() {
	
	//update directional light direction
	for (int i = 0; i < scene->GameObjectCount(); i++)
	{
		scene->GetGameObject(i)->Update(GetDeltaTime());
	}

}
void MeshLoading::Draw() {
	//draw scene
	scene->Draw();	
}

void MeshLoading::DrawIMGUI()
{
	//draw imgui
	//start imgui frame
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();


	//do imgui buttons

	auto tempCameraSpeed = scene->GetCamera()->GetMoveSpeed();
	if (ImGui::DragFloat("Camera Move Speed", &tempCameraSpeed, 1, 0.5f, 200, "%.1f", 1.0f)) {
		scene->GetCamera()->SetMoveSpeed(tempCameraSpeed);
	}
	auto tempExposure = exposure;
	if (ImGui::DragFloat("Exposure", &tempExposure, 1, 0.1f, 10, "%.1f", 1.0f)) {
		exposure = tempExposure;
	}

	auto tempCameraTurnSpeed = scene->GetCamera()->GetTurnSpeed();
	if (ImGui::DragFloat("Camera Turn Speed", &tempCameraTurnSpeed, 0.005f, 0.001f, 0.5f, "%.1f", 1.0f)) {
		scene->GetCamera()->SetTurnSpeed(tempCameraTurnSpeed);
	}

	auto tempPos = scene->GetPointLights()[0]->GetDirection();
	if (ImGui::DragFloat3("Light 1 Position (XYZ)", &tempPos[0])) {
		scene->GetPointLights()[0]->SetDirection(tempPos);
	}
	auto tempColour = scene->GetPointLights()[0]->GetRawColour();
	if (ImGui::DragFloat3("Light 1 Colour", &tempColour[0], 0.01f, 0, 1, "%.2f", 1.0f)) {
		scene->GetPointLights()[0]->SetColour(tempColour, 50000);
	}

	auto tempPos2 = scene->GetPointLights()[1]->GetDirection();
	if (ImGui::DragFloat3("Light 2 Position (XYZ)", &tempPos2[0])) {
		scene->GetPointLights()[1]->SetDirection(tempPos2);
	}
	auto tempColour2 = scene->GetPointLights()[1]->GetRawColour();
	if (ImGui::DragFloat3("Light 2 Colour", &tempColour2[0], 0.01f, 0, 1, "%.2f", 1.0f)) {
		scene->GetPointLights()[1]->SetColour(tempColour2, 50000);
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
	if (ImGui::Button("Light Set Up 1")) {
		scene->GetPointLights()[0]->SetColour({ 1,1,1 }, 50000);
		scene->GetPointLights()[0]->SetDirection({ 105,105,105 });
		scene->GetPointLights()[1]->SetColour({ 0,0,0.5f }, 50000);
		scene->GetPointLights()[1]->SetDirection({ -10,-10,-10 });
		scene->GetDirectionalLight()->SetDirection(glm::normalize(glm::vec3((float)sin(1), 0.75f, (float)cos(0))));
	}

	scene->DrawIMGUI();

	scene->DrawCurrentSelectedObject();

	Managers::TextureManager::DrawImgui();
	Managers::MeshManager::DrawImgui();

	ImGui::Render();

	if (ImGui::GetDrawData()) {
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	}
}
