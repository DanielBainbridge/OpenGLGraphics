#include "MeshManager.h"
#include <filesystem>
#include "IMGUI_include.h"
using namespace std;
namespace Managers {
	
	void MeshManager::FindAllMeshes()
	{
		for (auto directory : filesystem::recursive_directory_iterator("Assets\\Meshes")) {
			if (directory.path().extension() == ".fbx" || directory.path().extension() == ".obj") {
				string newDirectory = directory.path().generic_string();
				meshManager->allMeshes.push_back(newDirectory);
			}
		}
	}
	void MeshManager::DrawImgui()
	{
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		//do stuff inside this window


		ImGui::Render();
	}

	MeshManager* MeshManager::meshManager = nullptr;
}