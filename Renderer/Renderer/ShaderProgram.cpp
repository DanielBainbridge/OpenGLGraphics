#include "ShaderProgram.h"
#include "Utility.h"
#include <iostream>

void ShaderProgram::LoadFromFiles(std::string vertexShaderFName, std::string fragmentShaderFName)
{
	//say that we have loaded correctly until proven otherwise
	loadedSuccessfully = true;

	vertexShaderID = glCreateShader(GL_VERTEX_SHADER);
	fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

	shaderProgramID = glCreateProgram();

	std::string vertexSource = LoadFileAsString(vertexShaderFName);
	std::string fragmentSource = LoadFileAsString(fragmentShaderFName);

	//error management
	//check vertex shader errors
	const char* vertexSourceC = vertexSource.c_str();

	glShaderSource(vertexShaderID, 1, &vertexSourceC, nullptr);
	glCompileShader(vertexShaderID);

	GLchar errorLog[512];
	GLint successStatus = 0;
	glGetShaderiv(vertexShaderID, GL_COMPILE_STATUS, &successStatus);
	if (successStatus == GL_FALSE) {
		std::cout << "Vertex Shader failed" << std::endl;
		glGetShaderInfoLog(vertexShaderID, 512, nullptr, errorLog);
		std::cout << errorLog << std::endl;
		loadedSuccessfully = false;
	}
	else
		std::cout << "Vertex Shader Successful" << std::endl;


	//check fragment shader errors
	const char* fragmentSourceC = fragmentSource.c_str();

	glShaderSource(fragmentShaderID, 1, &fragmentSourceC, nullptr);
	glCompileShader(fragmentShaderID);

	glGetShaderiv(vertexShaderID, GL_COMPILE_STATUS, &successStatus);
	if (successStatus == GL_FALSE) {
		std::cout << "Fragment Shader failed" << std::endl;
		glGetShaderInfoLog(vertexShaderID, 512, nullptr, errorLog);
		std::cout << errorLog << std::endl;
		loadedSuccessfully = false;
	}
	else
		std::cout << "Fragment Shader Successful" << std::endl;


	//link shader to itself and to the program
	glAttachShader(shaderProgramID, fragmentShaderID);
	glAttachShader(shaderProgramID, vertexShaderID);
	glLinkProgram(shaderProgramID);

	glGetProgramiv(shaderProgramID, GL_LINK_STATUS, &successStatus);

	//check if successfully linked
	if (successStatus == GL_FALSE) {
		std::cout << "Shader link failed" << std::endl;
		glGetProgramInfoLog(shaderProgramID, 512, nullptr, errorLog);
		std::cout << errorLog << std::endl;
		loadedSuccessfully = false;
	}

	//shader loaded with no errors
	if (loadedSuccessfully) {
		std::cout << "Shader loaded properly!" << std::endl;
	}

}

void ShaderProgram::Enable()
{
	glUseProgram(shaderProgramID);
}

ShaderProgram::~ShaderProgram()
{
}

void ShaderProgram::SetFloatUniform(std::string variableName, float value)
{
	GLint varLoc = glGetUniformLocation(shaderProgramID, variableName.c_str());
	glUniform1f(varLoc, value);
}

void ShaderProgram::SetMatrixUniform(std::string variableName, glm::mat4 value)
{
	GLint varLoc = glGetUniformLocation(shaderProgramID, variableName.c_str());

	glUniformMatrix4fv(varLoc, 1, GL_FALSE, &value[0][0]);
}
