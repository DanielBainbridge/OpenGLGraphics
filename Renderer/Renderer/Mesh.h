#pragma once
#include "Graphics.h"
#include "Texture.h"
class ShaderProgram;
class Mesh {
public:
	Mesh() : triCount(0), vao(0), vbo(0), ibo(0) {}
	virtual ~Mesh();

	struct Vertex {
		glm::vec4 position;
		glm::vec4 normal;
		glm::vec2 texCoord;
		glm::vec4 tangent;
	};

	void InitialiseQuad();
	virtual void Draw();
	//takes an array of vertices,a count of vertices
	void Initialise(unsigned int vertexCount, const Vertex* vertices, unsigned int indexCount, unsigned int* indicies);
	void InitialiseFromFile(std::string filename);
	void SetPosition(glm::vec3 position);
	void ApplyMaterial(ShaderProgram* shader);
	void LoadMaterial(std::string filename);
	void CalculateTangents(std::vector<Vertex> vertices, unsigned int vertexCount, const std::vector<unsigned int>& indices);
	glm::mat4 quadTransform =
	{ 1,0,0,0,
	0,1,0,0,
	0,0,1,0,
	0,0,0,1 };


protected:
	unsigned int triCount;
	//vertex array object, vertex buffer object, index buffer object
	unsigned int vao, vbo, ibo;
	glm::vec3 Ka; // ambient colour of surface
	glm::vec3 Kd; // diffuse colour of surface
	glm::vec3 Ks; //specular colour of surface
	float specularPower;

	Texture mapKd; // texture map diffuse
	Texture mapKs; // texture map specular
	Texture mapNormal; // texture map normal
};