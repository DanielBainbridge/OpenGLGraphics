#version 460

layout (location = 0) in vec4 Position;
layout (location = 1) in vec4 Normal;
layout (location = 2) in vec2 TexCoords;
layout (location = 3) in vec4 Tangent;
layout (location = 4) in ivec4 BoneID;
layout (location = 5) in vec4 Weights;

uniform mat4 ProjectionMatrix;
uniform mat4 ModelMatrix;

const int MAX_BONES = 100;
const int MAX_BONE_INFLUENCE = 4;
uniform mat4 FinalBonesMatrices[MAX_BONES];


out vec3 _Normal;
out vec4 _Position;
out vec2 _TexCoords;
out vec3 _Tangent;
out vec3 _BiTangent;
flat out ivec4 _BoneID;
out vec4 _Weights;

void main()
{
	vec4 posTransformed = vec4(0.0f);
	mat4 boneTransform = (FinalBonesMatrices[BoneID[0]] * Weights[0]);
	boneTransform += (FinalBonesMatrices[BoneID[1]] * Weights[1]);
	boneTransform += (FinalBonesMatrices[BoneID[2]] * Weights[2]);
	boneTransform += (FinalBonesMatrices[BoneID[3]] * Weights[3]);
		
	posTransformed = boneTransform * Position;


	_Position = ModelMatrix * posTransformed;
	_Normal = (ModelMatrix * Normal).xyz;
	_TexCoords = TexCoords;
	_Tangent = (ModelMatrix * vec4(Tangent.xyz,0)).xyz;
	_BiTangent = cross(_Normal, _Tangent) * Tangent.w;
	_BoneID = BoneID;
	_Weights = Weights;
	
	gl_Position = ProjectionMatrix * posTransformed;
}