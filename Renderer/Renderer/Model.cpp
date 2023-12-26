#include "Model.h"
#include "Animation.h"
#include "Animator.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include "ShaderProgram.h"
#include "assimp_glm_helpers.h"
#pragma region Model

Model::Model(Model& model)
{

}

void Model::Draw(ShaderProgram* shader)
{

	for (int i = 0; i < meshes.size(); i++)
	{		
		if (skinnedMesh) {
			auto transforms = animator->GetFinalBoneMatrices();
			for (int j = 0; j < transforms.size(); j++)
			{
				shader->bindUniform("FinalBonesMatrices[" + std::to_string(i) + "]", transforms[i]);
			}
		}
		meshes[i]->ApplyMaterial(shader);
		meshes[i]->Draw();
	}
}

void Model::InitialiseModelFromFile(std::string filename, bool isSkinned)
{
	skinnedMesh = isSkinned;

	//read vertices from model
	//aiPostProcessSteps steps = aiPro
	const aiScene* scene = aiImportFile(filename.c_str(),
		aiProcess_Triangulate |
		aiProcess_CalcTangentSpace |
		aiProcess_FlipUVs
	);
	//load meshes we find

	if (scene == nullptr) {
		std::cout << "Failed To Load: " << filename << std::endl;
		meshes.clear();
		meshes.reserve(0);
		return;
	}

	std::vector<aiMesh*> aiMeshes;

	for (int i = 0; i < scene->mNumMeshes; i++) {
		aiMeshes.push_back(scene->mMeshes[i]);
	}
	//load animations here with aiscene, fix up mesh cpp and h
	for (int i = 0; i < aiMeshes.size(); i++)	{
		meshes.push_back(Mesh::InitialiseFromAiMesh(aiMeshes[i], this, isSkinned));
		if (isSkinned) {
			animations.push_back(new Animation(filename, meshes[i]));
			animator = new Animator((animations[0]));
		}
	}
	materialFileNames.resize(meshes.size());
}

void Model::SetMaterial(int materialLocation, std::string filename)
{
	materialFileNames[materialLocation] = filename;
}

void Model::LoadMaterials() {
	for (int i = 0; i < meshes.size(); i++)
	{
		std::cout << "Material:" << i << materialFileNames[i] << std::endl;
		switch (shaderType)
		{
		case Model::PBR:
			meshes[i]->LoadPBRMaterial(materialFileNames[i]);
			meshes[i]->isPBR = true;
			break;
		case Model::PBRMask:
			meshes[i]->LoadPBRMaskMaterial(materialFileNames[i]);
			meshes[i]->isPBR = true;
			break;
		case Model::Specular:
			meshes[i]->LoadSpecularMaterial(materialFileNames[i]);
			break;
		}
	}
}

#pragma endregion