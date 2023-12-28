#include "Bone.h"
#include <gtx/quaternion.hpp>

float Bone::GetScaleFactor(float lastTimeStamp, float nextTimeStamp, float animationTime)
{
	float scaleFactor = 0.0f;
	float midWayLength = animationTime - lastTimeStamp;
	float framesDiff = nextTimeStamp - lastTimeStamp;
	scaleFactor = midWayLength / framesDiff;
	return scaleFactor;
}

glm::mat4 Bone::InterpolatePosition(float animationTime)
{
	if (1 == numPositions)
		return glm::translate(glm::mat4(1.0f), positions[0].position);
	int p0Index = GetPositionIndex(animationTime);
	int p1Index = p0Index + 1;
	float scaleFactor = GetScaleFactor(positions[p0Index].timeStamp, positions[p1Index].timeStamp, animationTime);
	glm::vec3 finalPosition = glm::mix(positions[p0Index].position, positions[p1Index].position, scaleFactor);
	return glm::translate(glm::mat4(1.0f), finalPosition);
}

glm::mat4 Bone::InterpolateRotation(float animationTime)
{
	if (1 == numRotations)
	{
		auto rotation = glm::normalize(rotations[0].rotation);
		return glm::toMat4(rotation);
	}

	int p0Index = GetRotationIndex(animationTime);
	int p1Index = p0Index + 1;
	float scaleFactor = GetScaleFactor(rotations[p0Index].timeStamp,
		rotations[p1Index].timeStamp, animationTime);
	glm::quat finalRotation = glm::slerp(rotations[p0Index].rotation,
		rotations[p1Index].rotation, scaleFactor);
	finalRotation = glm::normalize(finalRotation);
	return glm::toMat4(finalRotation);
}

glm::mat4 Bone::InterpolateScale(float animationTime)
{
	if (1 == numScales)
		return glm::scale(glm::mat4(1.0f), scales[0].scale);

	int p0Index = GetScaleIndex(animationTime);
	int p1Index = p0Index + 1;
	float scaleFactor = GetScaleFactor(scales[p0Index].timeStamp,
		scales[p1Index].timeStamp, animationTime);
	glm::vec3 finalScale = glm::mix(scales[p0Index].scale, scales[p1Index].scale
		, scaleFactor);
	return glm::scale(glm::mat4(1.0f), finalScale);
}

void Bone::Update(float animationTime)
{
	glm::mat4 translation = InterpolatePosition(animationTime);
	glm::mat4 rotation = InterpolateRotation(animationTime);
	glm::mat4 scale = InterpolateScale(animationTime);

	localTransform = translation * rotation * scale;
}

int Bone::GetPositionIndex(float animationTime)
{
	for (int index = 0; index < numPositions; index++)
	{
		if (animationTime < positions[index + 1].timeStamp)
		{
			return index;
		}
	}
	assert(0);
}

int Bone::GetRotationIndex(float animationTime)
{
	for (int index = 0; index < numRotations; index++)
	{
		if (animationTime < rotations[index + 1].timeStamp)
		{
			return index;
		}
	}
	assert(0);
}

int Bone::GetScaleIndex(float animationTime)
{
	for (int index = 0; index < numScales; index++)
	{
		if (animationTime < scales[index + 1].timeStamp)
		{
			return index;
		}
	}
	assert(0);
}
