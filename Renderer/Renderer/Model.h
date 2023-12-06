#pragma once
#include "Graphics.h"
#include "Texture.h"
#include <assimp/scene.h>
#include <assimp/cimport.h>
#include <assimp/postprocess.h>
#include <map>
#include "Mesh.h"

class ShaderProgram;

class Model {
public:
	enum ShaderType {
		PBR,
		PBRMask,
		Specular
	};

	struct Bone {
		int id;
		glm::mat4 offset;
	};

	Model() {};
	Model(Model& model);
	~Model();

	std::vector<Mesh*> GetMeshes() { return meshes; };
	virtual void Draw(ShaderProgram* shader);
	ShaderType shaderType = PBRMask;
	void InitialiseModelFromFile(std::string filename);
	void SetMaterial(int materialLocation, std::string filename);
	std::vector<std::string> GetMaterialFileNames() { return materialFileNames; }
	void LoadMaterials();
	auto& GetBoneMap() { return boneMap; };
	int& GetBoneCount() { return boneCounter; };
	void ExtractBoneWeightForVertices(std::vector<Mesh::Vertex> vertices, aiMesh* mesh, const aiScene* scene, Mesh* wholeMesh);

private:
	std::vector<Mesh*> meshes;
	std::vector<std::string> materialFileNames;
	std::map<std::string, Bone> boneMap;
	int boneCounter = 0;




};