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
#include "Animation.h"

class Animator {
public:
	Animator(Animation* animation);
	void UpdateAnimation(float deltaTime);
	void PlayAnimation(Animation* pAnimation);
	void CalculateBoneTransform(const AssimpNodeData* node, glm::mat4 parentTransform);
	std::vector<glm::mat4> GetFinalBoneMatrices() { return finalBoneMatrices; }

private:
	std::vector<glm::mat4> finalBoneMatrices;
	Animation* currentAnimation;
	float currentTime;
	float deltaTime;
};