#define STB_IMAGE_IMPLEMENTATION
#include "Texture.h"
#include "stb_image.h"


Texture::Texture()
{
}

Texture::Texture(std::string filename)
{
	LoadFromFile(filename);
}

Texture::~Texture()
{
	if (loadedProperly)
		glDeleteTextures(1, &textureID);
}

void Texture::LoadFromFile(std::string filename)
{
	unsigned char* imageData = stbi_load(filename.c_str(), &width, &height, &channelCount, 0);
	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_2D, textureID);

	if (channelCount == 3) {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, imageData);
	}
	else if (channelCount == 4) {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, imageData);
	}

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	glBindTexture(GL_TEXTURE_2D, 0);

	stbi_image_free(imageData);
	loadedProperly = true;
}

void Texture::Bind(int textureUnit) const
{
	glActiveTexture(GL_TEXTURE0 + textureUnit);
	glBindTexture(GL_TEXTURE_2D, textureID);
}

void Texture::Unbind(int textureUnit)
{
	glActiveTexture(GL_TEXTURE0 + textureUnit);
	glBindTexture(GL_TEXTURE_2D, 0);
}
