#pragma once
#include "Graphics.h"
#include "Texture.h"
#include <assimp/scene.h>
#include <assimp/cimport.h>
#include <assimp/postprocess.h>
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
	void ApplySpecularMaterial(ShaderProgram* shader);
	void ApplyPBRMaterial(ShaderProgram* shader);
	void ApplyPBRMaskMaterial(ShaderProgram* shader);
	void LoadSpecularMaterial(std::string filename);
	void LoadPBRMaterial(std::string filename);
	void LoadPBRMaskMaterial(std::string filename);
	void CalculateTangents(std::vector<Vertex> vertices, unsigned int vertexCount, const std::vector<unsigned int>& indices);
	inline void SetPBR(bool isTrue) { isPBR = isTrue; };

	glm::mat4 quadTransform =
	{ 1,0,0,0,
	0,1,0,0,
	0,0,1,0,
	0,0,0,1 };
	glm::vec2 UVTiling = { 1,1 };
	glm::vec2 UVOffset = {0,0};
	glm::vec2 maskUVTiling = {1,1};
	glm::vec2 maskUVOffset = {0,0};
	glm::vec2 emissiveUVTiling = {1,1};
	glm::vec2 emissiveUVOffset = { 0,0 };
	float emissiveIntensity = 0;
	glm::vec2 metallicUVTiling = {1,1};
	glm::vec2 metallicUVOffset = {0,0};
	glm::vec2 AOUVTiling = {1,1};
	glm::vec2 AOUVOffset = {0,0};
	glm::vec2 roughnessUVTiling = {1,1};
	glm::vec2 roughnessUVOffset = {0,0};
	glm::vec2 normalUVTiling = {1,1};
	glm::vec2 normalUVOffset = {0,0};


protected:

	bool isPBR = false;
	std::vector<std::string> materials;
	unsigned int triCount;
	//vertex array object, vertex buffer object, index buffer object
	unsigned int vao, vbo, ibo;

#pragma region SpecularVariables


	glm::vec3 Ka; // ambient colour of surface
	glm::vec3 Kd; // diffuse colour of surface
	glm::vec3 Ks; //specular colour of surface
	float specularPower;

	Texture mapKd; // texture map diffuse
	Texture mapKs; // texture map specular
	Texture mapNormal; // texture map normal
#pragma endregion


#pragma region PBRVariables

	glm::vec3 albedo;
	float metallic;
	float roughness;
	float ao;

	Texture albedoMap;
	Texture emissiveMap;
	Texture normalMap;
	Texture metallicMap;
	Texture roughnessMap;
	Texture aoMap;
	Texture maskMap;

#pragma endregion


};

class Model {
public:
	enum ShaderType {
		PBR,
		PBRMask,
		Specular
	};
	Model() {};
	Model(Model& model);
	~Model();
	virtual void Draw();
	ShaderType shaderType;


private:
	std::vector<Mesh*> meshes;
	std::vector<std::string> materialFileNames;

	void InitialiseMeshFromFile(std::string filename);
	void LoadMaterials();
};