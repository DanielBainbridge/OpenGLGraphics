#pragma once
#include <vector>
#include "Graphics.h"
#include "Utility.h"
namespace Managers
{
	class TextureManager {
	public:
		TextureManager(TextureManager& other) = delete; //can't copy
		void operator= (const TextureManager&) = delete; //can't assign
		static TextureManager* GetInstance() { if (textureManager == nullptr) { textureManager = new TextureManager(); } else { return textureManager; } };
		static std::vector<std::string> GetAllMeshes() { return textureManager->allTextures; };
		static void FindAllTextures();
		static void DrawImgui();

	private:
		TextureManager() {}
		static TextureManager* textureManager;
		std::vector<std::string> allTextures;
	};

}
