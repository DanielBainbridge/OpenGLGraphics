#include "TextureManager.h"
#include <filesystem>
#include "IMGUI_include.h"

using namespace std;
namespace Managers {

	void TextureManager::FindAllTextures()
	{
		for (auto directory : filesystem::recursive_directory_iterator("Textures")) {
			if (directory.path().extension() == ".tga" || directory.path().extension() == ".png" || directory.path().extension() == ".jpg") {
				string newDirectory = directory.path().generic_string();
				textureManager->allTextures.try_emplace(newDirectory, new Texture(newDirectory));
			}
		}
	}
	void TextureManager::DrawImgui()
	{
		ImGui::Begin("Texture Manager");
		ImGui::PushID("Texture Manager");
		if (ImGui::Button("Refresh Textures"))
		{
			FindAllTextures();
		}

		for (auto& [key, value] : textureManager->allTextures) {
			ImGui::Text(key.c_str());
		}


		ImGui::PopID();
		ImGui::End();
	}
	TextureManager* TextureManager::textureManager = nullptr;
}