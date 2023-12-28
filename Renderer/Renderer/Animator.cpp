#include "Animator.h"
#include "Bone.h"
#include "Animation.h"
#include <iostream>


Animator::Animator(Model* model)
{
	currentTime = 0;
	finalBoneMatrices.reserve(100);

	if (model->GetAnimations().size() > 0) {
		currentAnimation = model->GetAnimations()[0];
	}

	for (int i = 0; i < 100; i++)
	{
		finalBoneMatrices.push_back(glm::mat4(1.0));
	}
}



void Animator::UpdateAnimation(float deltaTime)
{
	this->deltaTime = deltaTime;
	if (currentAnimation) {

		currentTime += currentAnimation->GetTicksPerSecond() * deltaTime;
		currentTime = fmod(currentTime, currentAnimation->GetDuration());
		CalculateBoneTransform(&currentAnimation->GetRootNode(), glm::mat4(1.0f));
	}
}

void Animator::PlayAnimation(Animation* pAnimation)
{
	currentAnimation = pAnimation;
	currentTime = 0;
}

void Animator::CalculateBoneTransform(const AssimpNodeData* node, glm::mat4 parentTransform)
{
	std::string nodeName = node->name;
	glm::mat4 nodeTransform = node->transformation;

	Bone* bone = currentAnimation->FindBone(nodeName);
	if (bone) {
		bone->Update(currentTime);
		nodeTransform = bone->GetLocalTransform();
	}

	glm::mat4 globalTransformation = parentTransform * nodeTransform;

	auto boneInfoMap = currentAnimation->GetBoneMapID();
	if (boneInfoMap.find(nodeName) != boneInfoMap.end()) {
		int index = boneInfoMap[nodeName].id;		
		glm::mat4 offset = boneInfoMap[nodeName].offset;
		finalBoneMatrices[index] = globalTransformation * offset;
	}
	for (int i = 0; i < node->children.size(); i++)
	{
		CalculateBoneTransform(&node->children[i], globalTransformation);
	}
}

void Animator::PrintNodeHeirarchy()
{
	PrintNode(currentAnimation->GetRootNode(), 0);
}

void Animator::PrintNode(AssimpNodeData nodeToPrint, int depth)
{
	for (int i = 0; i < depth; i++)
	{
		std::cout << "  ";
	}
	std::cout << nodeToPrint.name << " Depth: " << depth << std::endl;
	for (int i = 0; i < nodeToPrint.childrenCount; i++)
	{
		PrintNode(nodeToPrint.children[i], depth + 1);
	}
}
