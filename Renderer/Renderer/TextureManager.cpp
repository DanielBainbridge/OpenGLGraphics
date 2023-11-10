#include "TextureManager.h"
#include <filesystem>
#include "IMGUI_include.h"

using namespace std;
namespace Managers {

	void TextureManager::FindAllTextures()
	{
		for (auto directory : filesystem::recursive_directory_iterator("Assets\\Textures")) {
			if (directory.path().extension() == ".tga" || directory.path().extension() == ".png" || directory.path().extension() == ".jpg") {
				string newDirectory = directory.path().generic_string();
				textureManager->allTextures.push_back(newDirectory);
			}
		}
	}
	void TextureManager::DrawImgui()
	{

	}
	TextureManager* TextureManager::textureManager = nullptr;
}