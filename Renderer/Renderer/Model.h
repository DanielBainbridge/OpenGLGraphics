#pragma once
#include "Graphics.h"
#include "Texture.h"
#include <assimp/scene.h>
#include <assimp/cimport.h>
#include <assimp/postprocess.h>
#include <map>
#include "Mesh.h"

class ShaderProgram;
class Animation;
class Animator;

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

	std::vector<Mesh*> GetMeshes() { return meshes; };
	virtual void Draw(ShaderProgram* shader);
	ShaderType shaderType = PBRMask;
	void InitialiseModelFromFile(std::string filename, bool isSkinned = false);
	void SetMaterial(int materialLocation, std::string filename);
	std::vector<std::string> GetMaterialFileNames() { return materialFileNames; }
	void LoadMaterials();
	Animator* GetAnimator() { return animator; }
	std::vector<Animation*> GetAnimations() { return animations; }
private:
	std::vector<Mesh*> meshes;
	Animator* animator;
	std::vector<Animation*> animations;
	std::vector<std::string> materialFileNames;
	bool skinnedMesh = false;

};