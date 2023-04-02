#pragma once
#include "Graphics.h"
class Texture {
public:
	Texture();
	Texture(std::string filename);
	~Texture();

	void LoadFromFile(std::string filename);
	Texture(const Texture& other) = delete;
	Texture& operator=(const Texture& other) = delete;
	void Bind(int textureUnit = 0) const;
	static void Unbind(int textureUnit = 0);

private:
	GLuint textureID;
	int width, height, channelCount;
	bool loadedProperly = false;
};