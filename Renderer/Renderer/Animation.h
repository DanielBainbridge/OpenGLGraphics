#pragma once
#include "Graphics.h"
#include "Utility.h"
#include <assimp/scene.h>
#include <assimp/cimport.h>
#include <assimp/postprocess.h>
#include <assimp/Importer.hpp>
#include "assimp_glm_helpers.h"
#include "Mesh.h"
#include "Bone.h"

struct AssimpNodeData {
	glm::mat4 transformation;
	std::string name;
	int childrenCount;
	std::vector<AssimpNodeData> children;
};

class Animation {
public:
	Animation() = default;
	Animation(const aiScene* scene, Model* model, int animationPos);
	~Animation() {}

	Bone* FindBone(const std::string& name);
	inline float GetTicksPerSecond() { return ticksPerSecond; }
	inline float GetDuration() { return duration; }
	inline const AssimpNodeData& GetRootNode() { return rootNode; }
	inline const std::map<std::string, Mesh::BoneInfo>& GetBoneMapID() { return boneInfoMap; }

private:
	float duration;
	int ticksPerSecond;
	std::vector<Bone> bones;
	AssimpNodeData rootNode;
	std::map<std::string, Mesh::BoneInfo> boneInfoMap;

	void ReadMissingBones(const aiAnimation* animation, Model& model);
	void ReadHeirarchyData(AssimpNodeData& destination, const aiNode* src);



};

