#include "MeshManager.h"
#include <filesystem>
#include "IMGUI_include.h"
using namespace std;
namespace Managers {
	
	void MeshManager::FindAllMeshes()
	{
		for (auto directory : filesystem::recursive_directory_iterator("Meshes")) {
			if (directory.path().extension() == ".fbx" || directory.path().extension() == ".obj") {
				string newDirectory = directory.path().generic_string();
				meshManager->allMeshes.try_emplace(newDirectory, new Model(newDirectory, true));
			}
		}
	}
	void MeshManager::DrawImgui()
	{
		ImGui::Begin("Mesh Manager");
		ImGui::PushID("Mesh Manager");
		if (ImGui::Button("Refresh Meshes"))
		{
			FindAllMeshes();
		}

		for (auto& [key, value] : meshManager->allMeshes) {
			ImGui::Text(key.c_str());
		}

		ImGui::PopID();
		ImGui::End();
	}

	MeshManager* MeshManager::meshManager = nullptr;
}