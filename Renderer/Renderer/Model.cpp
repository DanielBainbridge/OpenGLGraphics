#include "Model.h"
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
		meshes[i]->ApplyMaterial(shader);
		meshes[i]->Draw();
	}
}

void Model::InitialiseModelFromFile(std::string filename)
{
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

	for (int i = 0; i < aiMeshes.size(); i++)
	{
		meshes.push_back(Mesh::InitialiseFromAiMesh(aiMeshes[i], this));
		ExtractBoneWeightForVertices(meshes[i]->GetVertices(), aiMeshes[i], scene, meshes[i]);

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

void Model::ExtractBoneWeightForVertices(std::vector<Mesh::Vertex> vertices, aiMesh* mesh, const aiScene* scene, Mesh* wholeMesh)
{
	for (int boneIndex = 0; boneIndex < mesh->mNumBones; boneIndex++)
	{
		int boneID = -1;
		std::string boneName = mesh->mBones[boneIndex]->mName.C_Str();
		if (boneMap.find(boneName) == boneMap.end()) {
			Bone newBone;
			newBone.id = boneCounter;
			newBone.offset = AssimpGLMHelpers::ConvertMatrixToGLMFormat(mesh->mBones[boneIndex]->mOffsetMatrix);
			boneMap[boneName] = newBone;
			boneID = boneCounter;
			boneCounter++;
		}
		else {
			boneID = boneMap[boneName].id;
		}
		assert(boneID != -1);
		auto weights = mesh->mBones[boneIndex]->mWeights;
		int numWeights = mesh->mBones[boneIndex]->mNumWeights;

		for (int weightIndex = 0; weightIndex < numWeights; weightIndex++)
		{
			int vertexId = weights[weightIndex].mVertexId;
			float weight = weights[weightIndex].mWeight;
			assert(vertexId <= vertices.size());
			wholeMesh->SetVertexBoneData(vertices[vertexId], boneID, weight);
		}
	}
}



#pragma endregion