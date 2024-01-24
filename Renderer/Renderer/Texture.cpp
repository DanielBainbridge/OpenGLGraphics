#define STB_IMAGE_IMPLEMENTATION
#include "Texture.h"
#include "stb_image.h"
#include <iostream>


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
		glDeleteTextures(1, &textureID[0]);
}

void Texture::LoadFromFile(std::string filename)
{
	unsigned char* imageData = stbi_load(filename.c_str(), &width, &height, &channelCount, 0);
	glGenTextures(1, &textureID[0]);
	glBindTexture(GL_TEXTURE_2D, textureID[0]);

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

void Texture::CreateScreenSpaceTexture(int windowWidth, int windowHeight)
{
	glGenTextures(2, textureID);
	for (unsigned int i = 0; i < 2; i++)
	{
		glBindTexture(GL_TEXTURE_2D, textureID[i]);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA16F, windowWidth, windowHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + i, GL_TEXTURE_2D, textureID[i], 0);
	}
}

void Texture::CreateScreenSpacePingPongTexture(int windowWidth, int windowHeight, unsigned int* pingPongFBO)
{
	glGenFramebuffers(2, pingPongFBO);
	glGenTextures(2, textureID);
	for (unsigned int i = 0; i < 2; i++) {
		glBindFramebuffer(GL_FRAMEBUFFER, pingPongFBO[i]);
		glBindTexture(GL_TEXTURE_2D, textureID[i]);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA16F, windowWidth, windowHeight, 0, GL_RGBA, GL_FLOAT, NULL);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE); // we clamp to the edge as the blur filter would otherwise sample repeated texture values!
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, textureID[i], 0);
		// also check if framebuffers are complete (no need for depth buffer)
		if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
			std::cout << "Framebuffer not complete!" << std::endl;
	}
}



void Texture::Bind(int textureUnit, unsigned int ID) const
{
	glActiveTexture(GL_TEXTURE0 + textureUnit);
	glBindTexture(GL_TEXTURE_2D, textureID[ID]);
}

void Texture::Unbind(int textureUnit)
{
	glActiveTexture(GL_TEXTURE0 + textureUnit);
	glBindTexture(GL_TEXTURE_2D, 0);
}
