#include "GameObject.h"
#include "Mesh.h"
#include "ShaderProgram.h"
#include "Camera.h"
#include "Scene.h"
#include "Light.h"
#include "IMGUI_include.h"


GameObject::GameObject(glm::mat4 transform, Model* model, ShaderProgram* shaderProgram)
{
	this->transform = transform;
	this->model = model;
	shader = shaderProgram;
}

void GameObject::SetTransform(glm::vec3 position, glm::vec3 eulerAngles, glm::vec3 scale)
{
	this->position = position;
	this->rotation = eulerAngles;
	this->scale = scale;

	transform = glm::translate(glm::mat4(1), position)
		* glm::rotate(glm::mat4(1), glm::radians(eulerAngles.z), glm::vec3(0, 0, 1))
		* glm::rotate(glm::mat4(1), glm::radians(eulerAngles.y), glm::vec3(0, 1, 0))
		* glm::rotate(glm::mat4(1), glm::radians(eulerAngles.x), glm::vec3(1, 0, 0))
		* glm::scale(glm::mat4(1), scale);
}

void GameObject::SetPosition(glm::vec3 position)
{
	this->position = position;
	transform = glm::translate(glm::mat4(1), position)
		* glm::rotate(glm::mat4(1), glm::radians(rotation.z), glm::vec3(0, 0, 1))
		* glm::rotate(glm::mat4(1), glm::radians(rotation.y), glm::vec3(0, 1, 0))
		* glm::rotate(glm::mat4(1), glm::radians(rotation.x), glm::vec3(1, 0, 0))
		* glm::scale(glm::mat4(1), scale);
}

void GameObject::SetRotationEuler(glm::vec3 eulerAngles)
{
	rotation = eulerAngles;
	transform = glm::translate(glm::mat4(1), position)
		* glm::rotate(glm::mat4(1), glm::radians(eulerAngles.z), glm::vec3(0, 0, 1))
		* glm::rotate(glm::mat4(1), glm::radians(eulerAngles.y), glm::vec3(0, 1, 0))
		* glm::rotate(glm::mat4(1), glm::radians(eulerAngles.x), glm::vec3(1, 0, 0))
		* glm::scale(glm::mat4(1), scale);
}

void GameObject::SetScale(glm::vec3 scale)
{
	this->scale = scale;
	transform = glm::translate(glm::mat4(1), position)
		* glm::rotate(glm::mat4(1), glm::radians(rotation.z), glm::vec3(0, 0, 1))
		* glm::rotate(glm::mat4(1), glm::radians(rotation.y), glm::vec3(0, 1, 0))
		* glm::rotate(glm::mat4(1), glm::radians(rotation.x), glm::vec3(1, 0, 0))
		* glm::scale(glm::mat4(1), scale);
}

void GameObject::Draw(Scene* scene)
{
	//enable shader
	shader->Enable();
	//bind position
	auto pvm = scene->GetCamera()->GetProjectionMatrix(scene->GetWindowSize().x, scene->GetWindowSize().y) * scene->GetCamera()->GetViewMatrix() * transform;
	shader->bindUniform("ProjectionMatrix", pvm);

	//bind model
	shader->bindUniform("ModelMatrix", transform);
	//bind lighting
	shader->bindUniform("AmbientColour", scene->GetAmbientLight());
	shader->bindUniform("LightColour", scene->GetDirectionalLight()->GetColour());
	shader->bindUniform("LightDirection", scene->GetDirectionalLight()->GetDirection());
	//bind camera position
	shader->bindUniform("CameraPosition", scene->GetCamera()->GetPosition());

	int numLights = scene->GetNumLights();
	shader->bindUniform("numLights", numLights);
	shader->bindUniform("PointLightPosition", numLights, scene->GetPointLightPositions());
	shader->bindUniform("PointLightColour", numLights, scene->GetPointLightColours());

	model->Draw(shader);
}

void GameObject::DrawIMGUI()
{

	//do stuff inside this window
	ImGui::Begin((name + " Object").c_str());
	ImGui::PushID((name + " Object").c_str());

	//transform information position, rotation, scale

	if (ImGui::CollapsingHeader("Game Object Transform")) {
		ImGui::Indent();
		auto guiPosition = position;
		if (ImGui::DragFloat3("Game Object Position", &guiPosition[0], 1, -10000000, 10000000, "%0.2f", 1.0f)) {
			SetPosition(guiPosition);
		}
		auto guiRotation = rotation;
		if (ImGui::DragFloat3("Game Object Rotation", &guiRotation[0], 0.5f, -180, 180, "%.2f", 1.0f)) {
			SetRotationEuler(guiRotation);
		}
		auto guiScale = scale;
		if (ImGui::DragFloat3("Game Object Scale", &guiScale[0], 0.1f, 0.01f, 1000, "%0.2f", 1.0f)) {
			SetScale(guiScale);
		}
		ImGui::Unindent();
	}

	ImGui::Separator();
	//drop down of all models

	if (ImGui::CollapsingHeader("Model Meshes")) {

		if (ImGui::Button("Load Materials")) {
			model->LoadMaterials();
		}
		for (int i = 0; i < model->GetMeshes().size(); i++)
		{
			ImGui::Indent();
			if (ImGui::CollapsingHeader(("Mesh: " + std::to_string(i + 1)).c_str())) {

				ImGui::Indent();
				if (ImGui::CollapsingHeader(("Mesh: " + std::to_string(i + 1) + " Transform").c_str())) {
					ImGui::Indent();
					auto guiMeshPosition = model->GetMeshes()[i]->position;
					if (ImGui::DragFloat3(("Mesh: " + std::to_string(i + 1) + " Position").c_str(), &guiMeshPosition[0], 1, -10000000, 10000000, "%0.2f", 1.0f)) {
						model->GetMeshes()[i]->SetPosition(guiMeshPosition);
					}
					auto guiMeshRotation = model->GetMeshes()[i]->rotation;
					if (ImGui::DragFloat3(("Mesh: " + std::to_string(i + 1) + " Rotation").c_str(), &guiMeshRotation[0], 0.5f, -180, 180, "%.2f", 1.0f)) {
						model->GetMeshes()[i]->SetRotationEuler(guiMeshRotation);
					}
					auto guiMeshScale = model->GetMeshes()[i]->scale;
					if (ImGui::DragFloat3(("Mesh: " + std::to_string(i + 1) + " Scale").c_str(), &guiMeshScale[0], 0.1f, 0.01f, 1000, "%0.2f", 1.0f)) {
						model->GetMeshes()[i]->SetScale(guiMeshScale);
					}
					ImGui::Unindent();
				}


				if (ImGui::CollapsingHeader(("Mesh: " + std::to_string(i + 1) + " Material").c_str())) {

					ImGui::Indent();

					auto materialString = model->GetMaterialFileNames()[i];
					if (ImGui::InputText((name + "Mesh: " + std::to_string(i + 1) + " Material").c_str(), &materialString)) {
						model->SetMaterial(i, materialString);
					}

					auto UVTiling = model->GetMeshes()[i]->UVTiling;
					if (ImGui::DragFloat2((name + "Mesh: " + std::to_string(i + 1) + " Tiling").c_str(), &UVTiling[0], 0.05f, 0.01f, 10, "%.2f", 1.0f)) {
						model->GetMeshes()[i]->UVTiling = UVTiling;
					}

					auto UVOffset = model->GetMeshes()[i]->UVOffset;
					if (ImGui::DragFloat2((name + "Mesh: " + std::to_string(i + 1) + " Offset").c_str(), &UVOffset[0], 0.5f, 0, 1, "%.2f", 1.0f)) {
						model->GetMeshes()[i]->UVOffset = UVOffset;
					}

					auto EmissiveUVTiling = model->GetMeshes()[i]->emissiveUVTiling;
					if (ImGui::DragFloat2((name + "Mesh: " + std::to_string(i + 1) + " Emissive Tiling").c_str(), &EmissiveUVTiling[0], 0.05f, 0.01f, 10, "%.2f", 1.0f)) {
						model->GetMeshes()[i]->emissiveUVTiling = EmissiveUVTiling;
					}

					auto EmissiveUVOffset = model->GetMeshes()[i]->emissiveUVOffset;
					if (ImGui::DragFloat2((name + "Mesh: " + std::to_string(i + 1) + " Emissive Offset").c_str(), &EmissiveUVOffset[0], 0.5f, 0, 1, "%.2f", 1.0f)) {
						model->GetMeshes()[i]->emissiveUVOffset = EmissiveUVOffset;
					}
					auto EmissiveIntensity = model->GetMeshes()[i]->emissiveIntensity;
					if (ImGui::DragFloat((name + "Mesh: " + std::to_string(i + 1) + " Emissive Intensity").c_str(), &EmissiveIntensity, 0.05f, 0, 10, "%.2f", 1.0f)) {
						model->GetMeshes()[i]->emissiveIntensity = EmissiveIntensity;
					}
					ImGui::Unindent();

				}
				ImGui::Unindent();
			}
			ImGui::Unindent();
		}

	}

	//if model != null, get list of all meshes, for each mesh have drop down for material to use

	//each mesh check if it is using PBR mask PBR or specular, have tiling and offset options and emission options for each.

	//have hot reload game object button that loads model and such
	ImGui::PopID();
	ImGui::End();

}
