#include "Animation.h"
#include <iostream>
#include "Model.h"

Animation::Animation(const aiScene* scene, Model* model, int animationPos)
{
	assert(scene && scene->mRootNode);
	auto animation = scene->mAnimations[animationPos];
	duration = animation->mDuration;
	ticksPerSecond = animation->mTicksPerSecond;
	ReadHeirarchyData(rootNode, scene->mRootNode);
	ReadMissingBones(animation, *model);
}

Bone* Animation::FindBone(const std::string& name)
{
	auto iter = std::find_if(bones.begin(), bones.end(),
		[&](const Bone& Bone)
		{
			return Bone.GetBoneName() == name;
		}
	);
	if (iter == bones.end()) return nullptr;
	else return &(*iter);
}

void Animation::ReadMissingBones(const aiAnimation* animation, Model& model)
{
	int size = animation->mNumChannels;

	auto& boneMap = model.GetBoneMap();

	int& boneCount = model.GetBoneCount();

	for (int i = 0; i < size; i++)
	{
		auto channel = animation->mChannels[i];
		std::string boneName = channel->mNodeName.data;

		if (boneMap.find(boneName) == boneMap.end()) {
			boneMap[boneName].id = boneCount;
			boneCount++;
		}
		bones.push_back(Bone(boneName, boneMap[channel->mNodeName.data].id, channel));
	}
	boneInfoMap = boneMap;
}

void Animation::ReadHeirarchyData(AssimpNodeData& destination, const aiNode* src)
{
	assert(src);

	destination.name = src->mName.data;
	destination.transformation = AssimpGLMHelpers::ConvertMatrixToGLMFormat(src->mTransformation);
	destination.childrenCount = src->mNumChildren;

	for (int i = 0; i < src->mNumChildren; i++)
	{
		AssimpNodeData newData;
		ReadHeirarchyData(newData, src->mChildren[i]);
		destination.children.push_back(newData);
	}
}

