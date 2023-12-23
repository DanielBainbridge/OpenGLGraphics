#pragma once
#include "Graphics.h"
#include "Utility.h"
#include <assimp/scene.h>
#include <assimp/cimport.h>
#include <assimp/postprocess.h>
#include "assimp_glm_helpers.h"

struct KeyPosition {
	glm::vec3 position;
	float timeStamp;
};
struct KeyRotation {
	glm::quat rotation;
	float timeStamp;
};
struct KeyScale {
	glm::vec3 scale;
	float timeStamp;
};


class Bone {
private:
	std::vector<KeyPosition> positions;
	std::vector<KeyRotation> rotations;
	std::vector<KeyScale> scales;

	int numPositions;
	int numRotations;
	int numScales;

	glm::mat4 localTransform;
	std::string boneName;
	int boneID;

	float GetScaleFactor(float lastTimeStamp, float nextTimeStamp, float animationTime);
	glm::mat4 InterpolatePosition(float animationTime);
	glm::mat4 InterpolateRotation(float animationTime);
	glm::mat4 InterpolateScale(float animationTime);

public:
	Bone(const std::string& name, int ID, const aiNodeAnim* channel) :
		boneName(name),
		boneID(ID),
		localTransform(1.0f) {
		numPositions = channel->mNumPositionKeys;
		for (int positionIndex = 0; positionIndex < numPositions; positionIndex++)
		{
			aiVector3D aiPosition = channel->mPositionKeys[positionIndex].mValue;
			float timeStamp = channel->mPositionKeys[positionIndex].mTime;
			KeyPosition data;
			data.position = AssimpGLMHelpers::GetGLMVec(aiPosition);
			data.timeStamp = timeStamp;
			positions.push_back(data);
		}
		numRotations = channel->mNumRotationKeys;
		for (int rotationIndex = 0; rotationIndex < numRotations; rotationIndex++)
		{
			aiQuaternion aiRotation = channel->mRotationKeys[rotationIndex].mValue;
			float timeStamp = channel->mRotationKeys[rotationIndex].mTime;
			KeyRotation data;
			data.rotation = AssimpGLMHelpers::GetGLMQuat(aiRotation);
			data.timeStamp = timeStamp;
			rotations.push_back(data);
		}
		numScales = channel->mNumScalingKeys;
		for (int scaleIndex = 0; scaleIndex < numScales; scaleIndex++)
		{
			aiVector3D aiScale = channel->mScalingKeys[scaleIndex].mValue;
			float timeStamp = channel->mScalingKeys[scaleIndex].mTime;
			KeyScale data;
			data.scale = AssimpGLMHelpers::GetGLMVec(aiScale);
			data.timeStamp = timeStamp;
			scales.push_back(data);
		}
	}
	void Update(float animationTime);
	glm::mat4 GetLocalTransform() { return localTransform; }
	std::string GetBoneName() const { return boneName; }
	int GetBoneID() { return boneID; }
	int GetPositionIndex(float animationTime);
	int GetRotationIndex(float animationTime);
	int GetScaleIndex(float animationTime);
};