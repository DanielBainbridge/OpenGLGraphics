#pragma once
#include "Graphics.h"
class Texture {
public:
	Texture();
	Texture(std::string filename);
	~Texture();

	void LoadFromFile(std::string filename);
	void CreateScreenSpaceTexture(int windowWidth, int windowHeight);
	void CreateScreenSpacePingPongTexture(int windowWidth, int windowHeight, unsigned int* pingPongFBO);
	Texture(const Texture& other) = delete;
	unsigned int* GetTextureID() { return textureID; };
	Texture& operator=(const Texture& other) = delete;
	void Bind(int textureUnit = 0, unsigned int ID = 0) const;
	static void Unbind(int textureUnit = 0);

private:
	unsigned int textureID[2];
	int width, height, channelCount;
	bool loadedProperly = false;
};