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

	void SetFloatUniform(std::string variableName, float value);
	void SetMatrixUniform(std::string variableName, glm::mat4 value);
	void SetVectorUniform(std::string variableName, glm::vec3 value);
};