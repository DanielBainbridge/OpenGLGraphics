#include "Animation.h"

Animation::Animation(const std::string& animationPath, Mesh* mesh)
{
	Assimp::Importer importer;
	const aiScene* scene = importer.ReadFile(animationPath, aiProcess_Triangulate);
	assert(scene && scene->mRootNode);
	auto animation = scene->mAnimations[0];
	duration = animation->mDuration;
	ticksPerSecond = animation->mTicksPerSecond;
	ReadHeirarchyData(rootNode, scene->mRootNode);
	ReadMissingBones(animation, *mesh);
}

void Animation::ReadMissingBones(const aiAnimation* animation, Mesh& mesh)
{
	int size = animation->mNumChannels;

	auto& boneMap = mesh.GetBoneMap();
	int& boneCount = mesh.GetBoneCount();

	for (int i = 0; i < size; i++)
	{
		auto channel = animation->mChannels[i];
		std::string boneName = channel->mNodeName.data;
		if (boneMap.find(boneName) == boneMap.end()) {
			boneMap[boneName].id = boneCount;
			boneCount++;
		}
		bones.push_back(Bone(boneName, boneMap[boneName].id, channel));
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
