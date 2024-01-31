#pragma once
#include <vector>
#include <map>
#include "Graphics.h"
#include "Texture.h"
#include "Utility.h"
namespace Managers
{
	class TextureManager {
	public:
		TextureManager(TextureManager& other) = delete; //can't copy
		void operator= (const TextureManager&) = delete; //can't assign
		static TextureManager* GetInstance() { if (textureManager == nullptr) { textureManager = new TextureManager(); } else { return textureManager; } };
		static std::map<std::string, Texture*> GetAllTextures() { return textureManager->allTextures; };
		static void CreateMaterial();
		static void FindAllTextures();
		static void DrawImgui();

	private:
		TextureManager() {}
		static TextureManager* textureManager;
		std::map<std::string, Texture*> allTextures;
	};

}
