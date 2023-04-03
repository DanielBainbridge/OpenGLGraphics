#pragma once
#include "glm.hpp"
#include <string>
#include "Graphics.h"

class ShaderProgram {
	//ID's
	GLuint vertexShaderID;
	GLuint fragmentShaderID;
	GLuint shaderProgramID;
	bool loadedSuccessfully = false;

public:
	ShaderProgram(){}
	//loads a shader program from a fragment and vertex shader
	void LoadFromFiles(std::string vertexShaderFName, std::string fragmentShaderFName);
	void Enable();

	//rule of 3
	~ShaderProgram();
	ShaderProgram(const ShaderProgram& other) = delete;
	ShaderProgram& operator=(const ShaderProgram& other) = delete;

	void bindUniform(std::string variableName, int value);
	void bindUniform(std::string variableName, float value);
	void bindUniform(std::string variableName, const glm::vec2& value);
	void bindUniform(std::string variableName, const glm::vec3& value);
	void bindUniform(std::string variableName, const glm::vec4& value);
	void bindUniform(std::string variableName, const glm::mat2& value);
	void bindUniform(std::string variableName, const glm::mat3& value);
	void bindUniform(std::string variableName, const glm::mat4& value);
};