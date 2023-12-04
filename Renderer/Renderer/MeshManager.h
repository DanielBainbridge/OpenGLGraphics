#pragma once
#include <vector>
#include "Graphics.h"
#include "Utility.h"
namespace Managers
{
	class MeshManager {
	public:
		MeshManager(MeshManager& other) = delete; //can't copy
		void operator= (const MeshManager&) = delete; //can't assign
		static MeshManager* GetInstance() { if (meshManager == nullptr) { meshManager = new MeshManager(); } else { return meshManager; } };
		static std::vector<std::string> GetAllMeshes() { return meshManager->allMeshes; };
		static void FindAllMeshes();
		static void DrawImgui();
	private:
		MeshManager() {}
		static MeshManager* meshManager;
		std::vector<std::string> allMeshes;
	};

}